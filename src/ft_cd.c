/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 16:42:41 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/03 19:04:16 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**		get_env_var is in parse_dollar.c
*/

static int	check_access(char *arg)
{
	if (access(arg, F_OK) == -1)
		return (error_return(cd_no_s_f_or_dir, arg));
	else
		return (error_return(cd_perm_denied, arg));
	return (1);
}

static int	treat_args(char **args, t_env **env_info, int *ret)
{
	char	*line;

	if (!ft_strcmp(args[1], "-"))
	{
		if (get_env_var("OLDPWD", *env_info))
			*ret = chdir(get_env_var("OLDPWD", *env_info));
		else
			return (error_return(cd_oldpwd_not_set, 0));
	}
	else if (args[1][0] == '~')
	{
		if (get_env_var("HOME", *env_info))
		{
			line = ft_strdup(get_env_var("HOME", *env_info));
			line = ft_strjoin_free_first(line, &(args[1][1]));
			*ret = chdir(line);
			ft_memdel((void **)&line);
		}
		else
			return (error_return(cd_home_not_set, 0));
	}
	else
		*ret = chdir(args[1]);
	return (0);
}

static int	treat_cd(char **args, t_env **env_info, int *ret)
{
	if (args[1])
	{
		if (treat_args(args, env_info, ret))
			return (1);
	}
	else
	{
		if (get_env_var("HOME", *env_info))
			*ret = chdir(get_env_var("HOME", *env_info));
		else
			return (error_return(cd_home_not_set, 0));
	}
	return (0);
}

int			ft_cd(char **args, t_env **env_info)
{
	int		ret;
	char	buf[PATH_LEN];
	char	path[PATH_LEN];

	ret = 0;
	ft_bzero(buf, PATH_LEN);
	ft_bzero(path, PATH_LEN);
	getcwd(buf, PATH_LEN);
	if (treat_cd(args, env_info, &ret))
		return (1);
	if (ret == -1)
		return (check_access(args[1]));
	else
	{
		if (args[1] && !ft_strcmp(args[1], "-") &&
				get_env_var("OLDPWD", *env_info))
			ft_printf("%s\n", get_env_var("OLDPWD", *env_info));
		getcwd(path, PATH_LEN);
		ft_setenv(env_info, "PWD", path, args);
		ft_setenv(env_info, "OLDPWD", buf, args);
	}
	return (1);
}
