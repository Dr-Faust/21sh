/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 14:55:14 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/28 19:15:52 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main_launch(char **args, t_env *env_info, char *path)
{
	pid_t	pid;
	int		status;
	char	**env;
	int		i;

	env = env_to_arr(env_info);
	if ((pid = fork()) == 0)
		execve(path, args, env);
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
	}
	return (1);
}

int			pipe_launch(char **args, t_env *env_info, int input, int output)
{
	pid_t	pid;
	char	**env;
	int		j;
	char 	*path;

	path = treat_path(args, env_info);
	if (path && !check_redirections(args, env_info, path))
	{
		if ((pid = fork()) == 0)
		{
			if(input != STDIN_FILENO)
			{
				dup2(input, STDIN_FILENO);
				close(input);
			}
			if(output != STDOUT_FILENO)
			{
				dup2(output, STDOUT_FILENO);
				close(output);
			}
			env = env_to_arr(env_info);
			execve(path, args, env);
			j = -1;
			while (env[++j])
				ft_memdel((void **)&(env[j]));
			ft_memdel((void **)&path);
		}
		return pid;
	}
	return (1);
}

int			main_execute(char **pipe_cmds, int n, t_env	**env_info,
			t_hist *hist, bool pipe_exist)
{
	char 	*path;
	char	**args;

	args = split_command(pipe_cmds[n]);
	if (!builtins_handler(args, env_info, hist))
	{
		if (!ft_strcmp(args[0], "exit"))
		{
			tcsetattr(STDIN_FILENO, TCSADRAIN, &g_info->default_term);
			tgetent(0, getenv("TERM"));
			ft_memdel((void **)&path);
			clean_up(args);
			return (0);
		}
		path = treat_path(args, *env_info);
		if (path && !check_redirections(args, *env_info, path))
		{
			if (!ft_strcmp(args[0], "cat"))
				tcsetattr(STDIN_FILENO, TCSADRAIN, &g_info->default_term);
			main_launch(args, *env_info, path);
		}
		if (!ft_strcmp(args[0], "cat") && !args[1] && pipe_exist == false)
			ft_putchar('\n');
	}
	ft_memdel((void **)&path);
	clean_up(args);
	return (1);
}

int 		pipe_execute(char **pipe_cmds, int n, t_env **env_info,
			t_hist *hist, bool pipe_exist)
{
	int 	i;
	int 	j;
	int 	input;
	int 	fds[2];
	char 	**args;
	char	*path;
	bool	builtin_found;
	char 	*builtins_str[] = {"cd", "env", "setenv", "unsetenv", "help",
								"history"};

	i = -1;
	input = STDIN_FILENO;
	builtin_found = false;
	while (++i < n)
	{
		args = split_command(pipe_cmds[i]);
		pipe(fds);
		j = -1;
		while (++j < 6)
			if (!ft_strcmp(args[0], builtins_str[j]))
			{
				builtin_found = true;
				if (fds[1] != STDOUT_FILENO)
				{
					dup2(fds[1], STDOUT_FILENO);
					close(fds[1]);
				}
				builtins_handler(args, env_info, hist);
			}
		if (builtin_found == false)
		{
			// path = treat_path(args, *env_info);
			// if (path && !check_redirections(args, *env_info, path))
			// {
			// 	if(input != STDIN_FILENO)
			// 	{
			// 		dup2(input, STDIN_FILENO);
			// 		close(input);
			// 	}
			// 	if(output != STDOUT_FILENO)
			// 	{
			// 		dup2(output, STDOUT_FILENO);
			// 		close(output);
			// 	}
				if (!ft_strcmp(args[0], "cat"))
					tcsetattr(input, TCSADRAIN, &g_info->default_term);
				if (pipe_launch(args, *env_info, input, fds[1]))
					return (1);
			// }
			if (!ft_strcmp(args[0], "cat") && !args[1] && pipe_exist == false)
				ft_putchar('\n');
			ft_memdel((void **)&path);
			close(fds[1]);
			input = fds[0];
		}
		clean_up(args);
	}
	if (input != STDIN_FILENO)
		dup2(input, STDIN_FILENO);
	return (1);
}

int			builtins_handler(char **args, t_env **env_info, t_hist *hist)
{
	if (!args[0])
		return (1);
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, env_info));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(args, *env_info));
	else if (!ft_strcmp(args[0], "setenv"))
		return (ft_setenv(env_info, args[1], args[2], args));
	else if (!ft_strcmp(args[0], "unsetenv"))
		return (ft_unsetenv(*env_info, args[1]));
	else if (!ft_strcmp(args[0], "help"))
		return (ft_help());
	else if (!ft_strcmp(args[0], "history"))
		return (print_history(hist));
	return (0);
}