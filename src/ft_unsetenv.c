/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 17:12:17 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/03 18:28:36 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env(t_env *env_info, char *var)
{
	while (env_info)
	{
		if (!ft_strcmp(env_info->name, var))
			return (1);
		env_info = env_info->next;
	}
	return (0);
}

static int	check_var(t_env *env_info, char *var)
{
	if (!var)
		return (error_return(unset_too_few_arg, 0));
	if (!is_env(env_info, var))
		return (error_return(unset_no_such_var, var));
	return (0);
}

int			ft_unsetenv(t_env *env_info, char *var)
{
	t_env	*tmp;
	t_env	*origin;

	origin = env_info;
	if (check_var(env_info, var))
		return (1);
	tmp = origin;
	while (origin)
	{
		if (!ft_strcmp(origin->name, var))
		{
			free(origin->name);
			free(origin->content);
			if (tmp)
				tmp->next = origin->next;
			free(origin);
			return (1);
		}
		tmp = origin;
		origin = origin->next;
	}
	return (1);
}
