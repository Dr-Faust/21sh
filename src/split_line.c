/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 20:33:41 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/16 14:50:30 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_up(char **args, char *cmd)
{
	int		i;

	i = -1;
	if (args && *args)
		while (args[++i])
			ft_memdel((void **)&(args[i]));
	ft_memdel((void **)&(args));
	ft_memdel((void **)&cmd);
}

static void	check_quote(char *str, int *i)
{
	if ((str[*i] == 34 || str[*i] == 39) &&
			valid_quote(str, *i + 1, str[*i]) != -1)
		*i = valid_quote(str, *i + 1, str[*i]);
	str[*i] ? (*i)++ : 0;
}

int			count_commands(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ';')
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != ';')
			check_quote(str, &i);
	}
	return (count);
}

int			split_line(char *line, t_env **env_info, t_hist *hist,
			char ***args)
{
	char			*cmd;
	int				i;
	int				numb;
	unsigned int	start;
	int				j;

	i = 0;
	numb = -1;
	while (++numb < count_commands(line))
	{
		while (line[i] && line[i] == ';')
			i++;
		start = (unsigned int)i;
		while (line[i] && line[i] != ';')
			check_quote(line, &i);
		cmd = ft_strsub(line, start, (size_t)(i - start));
		j = -1;
		while (cmd[++j])
			if (cmd[j] == '$' && cmd[j + 1] && ft_isalnum(cmd[j + 1]))
				cmd = parse_dollar(cmd, j, *env_info);
		args[numb] = split_command(cmd);
		j = execute(args[numb], env_info, hist);
		clean_up(args[numb], cmd);
	}
	return (j);
}
