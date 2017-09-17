/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:45:01 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/30 17:15:51 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		clean_env_info(t_env **env_info)
{
	if (!(*env_info))
		return ;
	if ((*env_info)->next != 0)
		clean_env_info(&(*env_info)->next);
	ft_memdel((void **)&((*env_info)->content));
	ft_memdel((void **)&((*env_info)->name));
	ft_memdel((void **)&(*env_info));
}

static void	set_clicolor(t_env **lst)
{
	if (*lst)
		set_clicolor(&((*lst)->next));
	else
	{
		if (!(*lst = (t_env *)malloc(sizeof(t_env))))
			error_exit(sh, mem_alloc_err);
		(*lst)->name = ft_strdup("CLICOLOR");
		(*lst)->content = ft_strdup("1");
		(*lst)->next = 0;
	}
}

static void	create_lst(t_env **lst, char *arr, int *color_flag)
{
	if (!(*lst = (t_env *)malloc(sizeof(t_env))))
		error_exit(sh, mem_alloc_err);
	(*lst)->name = ft_strndup(arr, '=');
	(*lst)->content = ft_strdup(ft_strchr(arr, '=') + 1);
	if (!ft_strcmp((*lst)->name, "SHLVL"))
		(*lst)->content[0] += 1;
	if (!ft_strcmp((*lst)->name, "CLICOLOR"))
		*color_flag = 0;
	(*lst)->next = 0;
}

static void	add_lst(t_env **lst, char *arr, int *color_flag)
{
	if (*lst)
		add_lst(&((*lst)->next), arr, color_flag);
	else
		create_lst(lst, arr, color_flag);
}

t_env		*get_env_info(char **arr)
{
	t_env	*env_info;
	int		i;
	int		color_flag;

	color_flag = 1;
	i = -1;
	env_info = 0;
	while (arr[++i])
		add_lst(&env_info, arr[i], &color_flag);
	if (color_flag)
		set_clicolor(&env_info);
	return (env_info);
}
