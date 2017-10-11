/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 17:13:47 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/22 19:39:37 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_up(char **arr)
{
	int		i;

	i = -1;
	if (!arr || !arr[0])
		return ;
	while (arr[++i])
		ft_memdel((void **)&(arr[i]));
	ft_memdel((void **)&(arr[i]));
	ft_memdel((void **)&arr);
}

static void	err_no_path(int ret, char *arg)
{
	if (ret == -1)
		error_return(sh, perm_denied, arg);
	else
		error_return(sh, com_not_found, arg);
}

char		*add_slash(char *path, char *command)
{
	if (!path || !command)
		return (0);
	if (path[ft_strlen(path) - 1] && path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin_free_first(path, "/");
	path = ft_strjoin_free_first(path, command);
//	ft_printf("\npath = %s\n", path);
	return (path);
}

char		*verif_access(char *command, t_env *env_info)
{
	char		**arr;
	static int	i;
	char		*path;
	int			ret;

	path = 0;
	arr = ft_strsplit(env_info->content, ':');
	i = -1;
	ret = 1;
	while (arr[++i])
	{
		path = ft_strdup(arr[i]);
		path = add_slash(path, command);
		if (access(path, F_OK) == 0)
			if ((ret = access(path, X_OK)) == 0)
				break ;
		ft_memdel((void **)&path);
		path = 0;
	}
	if (!path)
		err_no_path(ret, command);
	clean_up(arr);
	return (path);
}
