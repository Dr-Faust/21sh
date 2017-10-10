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

static int	launch(char **args, t_env *env_info, char *path)
{
	pid_t	pid;
	int		status;
	char	**env;
	int		i;

	env = env_to_arr(env_info);
	if ((pid = fork()) == -1)
		error_return(sh, err_cal_fork, NULL);
	else if (pid == 0)
		execve(path, args, env);
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

static int	check_path(char *path, char *arg)
{
	struct stat	buf;

	if ((lstat(path, &buf) != -1 && !S_ISREG(buf.st_mode))
		|| access(path, X_OK) != 0)
		return (error_return(sh, perm_denied, arg));
	return (0);
}

static char	*get_path(char *arg, t_env *env_info)
{
	if (env_info == 0)
		return (arg);
	while (env_info)
	{
		if (!ft_strcmp(env_info->name, "PATH"))
			break ;
		env_info = env_info->next;
	}
	if (env_info)
		return (verif_access(arg, env_info));
	else
		error_return(sh, no_s_f_or_dir, arg);
	return (0);
}

int			treat_path(char **args, t_env *env_info)
{
	char	*path;

	path = 0;
	if (ft_strchr(args[0], '/') || env_info == 0)
	{
		if (access(args[0], F_OK) == 0)
			path = ft_strdup(args[0]);
		else
			return (error_return(sh, no_s_f_or_dir, args[0]));
	}
	path = (!path) ? get_path(args[0], env_info) : path;
	if (path)
	{
		if (check_path(path, args[0]))
		{
			ft_memdel((void **)&path);
			return (1);
		}
		if (!check_redirections(args, env_info, path))
			launch(args, env_info, path);
		if (!ft_strcmp(args[0], "cat"))
			ft_putchar('\n');
	}
	return (1);
}
