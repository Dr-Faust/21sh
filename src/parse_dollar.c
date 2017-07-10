/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 20:33:09 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/05 15:08:07 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env_var(char *var, t_env *env_info)
{
	t_env	*tmp;

	tmp = env_info;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, var))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

static int	ft_isenv(t_env *env_info, char *var)
{
	while (env_info)
	{
		if (!ft_strcmp(env_info->name, var))
			return (1);
		env_info = env_info->next;
	}
	return (0);
}

char		*parse_dollar(char *line, int i, t_env *env_info)
{
	char	*var;
	char	*new_line;
	int		tmp;

	tmp = i + 1;
	while (ft_isalnum(line[tmp]) || line[tmp] == '_')
		tmp++;
	if (!(var = ft_strsub(line, (unsigned int)(i + 1),
					(size_t)(tmp - i - 1))))
		return (0);
	line[i] = '\0';
	new_line = ft_strdup(&(line[0]));
	if (ft_isenv(env_info, var))
		new_line = ft_strjoin_free_first(new_line, get_env_var(var, env_info));
	new_line = ft_strjoin_free_first(new_line, &(line[tmp]));
	ft_memdel((void **)&var);
	ft_memdel((void **)&line);
	return (new_line);
}
