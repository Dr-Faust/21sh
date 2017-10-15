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

int		main_launch(char **args, t_env *env_info, char *path)
{
	pid_t	pid;
	int		status;
	char	**env;
	int		i;

	env = env_to_arr(env_info);
	if ((pid = fork()) == 0)
	{
		if ((execve(path, args, env)) == -1)
			kill(getpid(),SIGTERM);
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
	return (1);
}

int		main_execute(t_pipe *p, t_env **env_info, t_hist **hist)
{
	char 	*path;
	char	**args;

	args = split_command(p->pipe_cmds[p->i]);
	if (!builtins_handler(args, env_info, *hist))
	{
		if (!ft_strcmp(args[0], "exit"))
		{
			tcsetattr(STDIN_FILENO, TCSADRAIN, &g_info->default_term);
			// tgetent(0, getenv("TERM"));
			clean_up(args);
			return (0);
		}
		path = treat_path(args, *env_info);
		if (path)
		{
			if (check_redirections(args, hist, p))
				return (1);
			if (!ft_strcmp(args[0], "cat"))
				tcsetattr(STDIN_FILENO, TCSADRAIN, &g_info->default_term);
			main_launch(args, *env_info, path);
		}
		if (!ft_strcmp(args[0], "cat") && !args[1] && p->pipe_found == false)
			ft_putchar('\n');
	}
	if (p->fds[0] > 6)
        close(p->fds[0]);
	return (1);
}