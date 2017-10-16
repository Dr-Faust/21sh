#include "minishell.h"

void	manage_child(t_pipe *p, pid_t pid)
{
	int 	status;

	close (p->fds[1]);
	close(0);   /* prepare to redirect stdin      */
    dup(p->fds[0]);      //stdin now reads from the pipe  
    close(p->fds[0]);   /* extra file descriptor          */
    waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
}

void	check_pipes_redirections(char **args, t_pipe *p)
{
	if (p->pipe_found)
		set_pipe_fd(p);
	if (p->r->write_found)
		set_write_fd(args, p->r->write_index);
	if (p->r->append_found)
		set_append_fd(args, p->r->append_index);
	if (p->r->read_found)
		set_read_fd(args, p->r->read_index);
	if (p->r->heredoc_found)
		set_heredoc_fd(p);
}

int		launch(char **args, t_env *env_info, t_pipe *p, char *path)
{
	pid_t	pid;
	char	**env;
	int		i;

	env = env_to_arr(env_info);
	if ((pid = fork()) == 0)
	{
		check_pipes_redirections(args, p);
		execve(path, args, env);
	}
	else if (pid < 0)
		error_return(sh, err_cal_fork, NULL);
	else
	{
		manage_child(p, pid);
		i = -1;
		while (env[++i])
			ft_memdel((void **)&(env[i]));
		ft_memdel((void **)&env);
		ft_memdel((void **)&path);
	}
	return (1);
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

	i = -1;
	p->input = STDIN_FILENO;
	while (++i < p->index)
	{
		pipe(p->fds);
		args = split_command(p->pipe_cmds[i]);
		builtin_found = pipe_builtin(args, env_info, p, *hist);
		if (builtin_found == false)
			if ((path = treat_path(args, *env_info)))
			{
				check_redirections(args, hist, p);
				launch(args, *env_info, p, path);
			}
		close(p->fds[1]);
		p->input = p->fds[0];
		clean_up(args);
	}
	if (p->input != STDIN_FILENO)
		dup2(p->input, STDIN_FILENO);
	return (1);
}