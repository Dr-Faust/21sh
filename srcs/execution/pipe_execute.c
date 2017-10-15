#include "minishell.h"

int		pipe_launch(char **args, t_env *env_info, t_pipe *p, char *path)
{
	pid_t	pid;
	char	**env;
	int		i;
	int 	status;

	env = env_to_arr(env_info);
	if ((pid = fork()) == 0)
	{
		set_pipe_fd(&(p->input), &(p->fds[1]));
		if (p->heredoc_found)
			set_heredoc_fd(p);
		if ((execve(path, args, env)) == -1)
			kill(getpid(), SIGTERM);
	}
	else if (pid < 0)
		error_return(sh, err_cal_fork, NULL);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		i = -1;
		while (env[++i])
			ft_memdel((void **)&(env[i]));
		ft_memdel((void **)&env);
		ft_memdel((void **)&path);
	}
	return pid;
}

bool	pipe_builtin(char **args, t_env **env_info, t_pipe *p, t_hist *hist)
{
	int 	i;
	bool	builtin_found;
	char 	*builtins_str[] = {"cd", "env", "setenv", "unsetenv", "help",
								"history"};

	i = -1;
	builtin_found = false;
	while (++i < 6)
		if (!ft_strcmp(args[0], builtins_str[i]))
		{
			builtin_found = true;
			if (p->fds[1] != STDOUT_FILENO)
			{
				dup2(p->fds[1], STDOUT_FILENO);
				close(p->fds[1]);
			}
			builtins_handler(args, env_info, hist);
		}
	return (builtin_found);
}

int 	pipe_execute(t_pipe *p, t_env **env_info, t_hist **hist)
{
	int 	i;
	char 	**args;
	bool	builtin_found;
	char	*path;

	i = 0;
	p->input = STDIN_FILENO;
	p->heredoc_found = false;
	while (i < p->i)
	{
		pipe(p->fds);
		args = split_command(p->pipe_cmds[i]);
		builtin_found = pipe_builtin(args, env_info, p, *hist);
		if (builtin_found == false)
		{
			path = treat_path(args, *env_info);
			if (path)
			{
				check_redirections(args, hist, p);
				pipe_launch(args, *env_info, p, path);
			}
		}
		close(p->fds[1]);
		p->input = p->fds[0];
		clean_up(args);
		i++;
	}
	if (p->input != STDIN_FILENO)
		 dup2(p->input, STDIN_FILENO);
	if (p->fds[0] > 6)
        close(p->fds[0]);
	return (1);
}