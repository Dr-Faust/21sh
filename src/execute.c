/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 14:55:14 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/16 15:50:01 by opodolia         ###   ########.fr       */
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
	pid = fork();
	if (pid == 0)
		execve(path, args, env);
	else if (pid < 0)
		ft_printf("21sh: error calling fork");
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
		return (error_return(min_perm_denied, arg));
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
		ft_printf("21sh: no such file or directory: %s\n", arg);
	return (0);
}

static int	treat_path(char **args, t_env *env_info)
{
	char	*path;

	path = 0;
	if (ft_strchr(args[0], '/') || env_info == 0)
	{
		if (access(args[0], F_OK) == 0)
			path = ft_strdup(args[0]);
		else
			return (error_return(min_no_s_f_or_dir, args[0]));
	}
	path = (!path) ? get_path(args[0], env_info) : path;
	if (path)
	{
		if (check_path(path, args[0]))
		{
			ft_memdel((void **)&path);
			return (1);
		}
		launch(args, env_info, path);
	}
	return (1);
}

int			execute(char **args, t_env **env_info)
{
	if (args[0] == NULL)
		return (1);
	if (!(ft_strcmp(args[0], "echo")))
		return (ft_echo(args));
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, env_info));
	if (!ft_strcmp(args[0], "env"))
		return (ft_env(*env_info));
	if (!ft_strcmp(args[0], "setenv"))
		return (ft_setenv(env_info, args[1], args[2], args));
	if (!ft_strcmp(args[0], "unsetenv"))
		return (ft_unsetenv(*env_info, args[1]));
	else if (!ft_strcmp(args[0], "help"))
		return (ft_help());
	else if (!ft_strcmp(args[0], "exit"))
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &default_term);
		return (0);
	}
	return (treat_path(args, *env_info));
}
