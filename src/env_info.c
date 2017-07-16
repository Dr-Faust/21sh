/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:45:01 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/16 14:50:07 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_clicolor(t_env **lst)
{
	if (*lst)
		set_clicolor(&((*lst)->next));
	else
	{
		if (!(*lst = (t_env *)malloc(sizeof(t_env))))
			return ;
		(*lst)->name = ft_strdup("CLICOLOR");
		(*lst)->content = ft_strdup("1");
		(*lst)->next = 0;
	}
}

static void	create_lst(t_env **lst, char *arr)
{
	if (!(*lst = (t_env *)malloc(sizeof(t_env))))
		return ;
	(*lst)->name = ft_strndup(arr, '=');
	(*lst)->content = ft_strdup(ft_strchr(arr, '=') + 1);
	if (!ft_strcmp((*lst)->name, "SHLVL"))
		(*lst)->content[0] += 1;
	(*lst)->next = 0;
}

static void	add_lst(t_env **lst, char *arr)
{
	if (*lst)
		add_lst(&((*lst)->next), arr);
	else
		create_lst(lst, arr);
}

t_env		*get_env_info(char **arr)
{
	t_env	*env_info;
	int		i;

	i = -1;
	env_info = 0;
	while (arr[++i])
		add_lst(&env_info, arr[i]);
	set_clicolor(&env_info);
	return (env_info);
}
