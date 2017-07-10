/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 20:05:07 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/03 20:13:07 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_to_env(t_env **env_info, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env_info;
	if (!tmp)
	{
		if (!(*env_info = (t_env *)malloc(sizeof(t_env))))
			return (1);
		(*env_info)->name = ft_strdup(var);
		(*env_info)->content = ft_strdup(value);
		(*env_info)->next = 0;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_env *)malloc(sizeof(t_env))))
			return (1);
		tmp->next->name = ft_strdup(var);
		tmp->next->content = ft_strdup(value);
		tmp->next->next = 0;
	}
	return (1);
}

static int	check_args(char *var, char *value, char **args)
{
	int		i;

	i = -1;
	if ((var == 0 || value == 0))
		return (error_return(set_too_few_arg, 0));
	else if (args[1] && args[2] && args[3])
		return (error_return(set_too_much_arg, 0));
	else
	{
		while (var[++i])
			if (ft_isdigit(var[i]))
				return (error_return(set_not_an_id, var));
	}
	return (0);
}

int			ft_setenv(t_env **env_info, char *var, char *value, char **args)
{
	t_env	*tmp;

	tmp = *env_info;
	if (check_args(var, value, args))
		return (1);
	while (tmp && tmp->next != NULL)
	{
		if (!ft_strcmp(tmp->name, var))
		{
			free(tmp->content);
			tmp->content = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	if (tmp && !ft_strcmp(tmp->name, var))
	{
		ft_memdel((void **)&(tmp->content));
		tmp->content = ft_strdup(value);
		return (1);
	}
	return (add_to_env(env_info, var, value));
}

int			ft_env(t_env *env_info)
{
	while (env_info != 0)
	{
		ft_printf("%s=%s\n", env_info->name, env_info->content);
		env_info = env_info->next;
	}
	return (1);
}
