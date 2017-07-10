/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 19:08:01 by opodolia          #+#    #+#             */
/*   Updated: 2017/06/22 17:32:53 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_line(t_env *env_info, char ***arr)
{
	int		i;
	int		j;
	int		k;
	t_env	*tmp;

	tmp = env_info;
	i = 0;
	while (tmp)
	{
		j = 0;
		k = 0;
		while (tmp->name[j])
		{
			(*arr)[i][j] = tmp->name[j];
			j++;
		}
		(*arr)[i][j] = '=';
		while (tmp->content[k])
		{
			(*arr)[i][j + 1 + k] = tmp->content[k];
			k++;
		}
		i++;
		tmp = tmp->next;
	}
}

static void	add_new_line(t_env *env_info, char ***arr)
{
	int		size;
	int		i;

	i = 0;
	while (env_info)
	{
		size = (int)(ft_strlen(env_info->name) +
				ft_strlen(env_info->content) + 1);
		if (!((*arr)[i] = ft_memalloc(sizeof(char) * (size + 1))))
			return ;
		i++;
		env_info = env_info->next;
	}
}

static int	env_size(t_env *env_info)
{
	int		size;

	size = 0;
	while (env_info)
	{
		size++;
		env_info = env_info->next;
	}
	return (size);
}

char		**env_to_arr(t_env *env_info)
{
	char	**arr;
	int		size;
	t_env	*tmp;

	tmp = env_info;
	size = env_size(env_info);
	if (!(arr = ft_memalloc(sizeof(char *) * (size + 1))))
		return (0);
	add_new_line(env_info, &arr);
	env_info = tmp;
	fill_line(env_info, &arr);
	return (arr);
}
