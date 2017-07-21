/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:40:58 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/21 17:22:16 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			valid_quote(char *s, int i, char quote)
{
	while (s[i])
	{
		if (s[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int			count_args(char *str)
{
	int		i;
	int		numb;

	i = 0;
	numb = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i])
			numb++;
		while (str[i] && !ft_isspace(str[i]))
		{
			if ((str[i] == 34 || str[i] == 39) &&
				valid_quote(str, i + 1, str[i]) != -1)
			{
				i = valid_quote(str, i + 1, str[i]);
				i++;
			}
			else
				i++;
		}
	}
	return (numb);
}

static void	split_quotes(char *line, char **args, int *i, int numb)
{
	int		start;

	if (line[*i] == 34 || line[*i] == 39)
	{
		start = *i + 1;
		*i = valid_quote(line, *i + 1, line[*i]);
		args[numb] = ft_strjoin_free(args[numb],
			ft_strsub(line, (unsigned int)start, (size_t)(*i - start)));
		(*i)++;
	}
	if (line[*i] != 34 && line[*i] != 39)
	{
		start = *i;
		while (line[*i])
		{
			if (line[*i] == 34 || line[*i] == 39 || ft_isspace(line[*i]))
				break ;
			(*i)++;
		}
		args[numb] = ft_strjoin_free(args[numb],
			ft_strsub(line, (unsigned int)start, (size_t)(*i - start)));
	}
}

char		**split_command(char *line)
{
	char	**args;
	int		args_numb;
	int		i;
	int		numb;

	i = 0;
	numb = 0;
	args_numb = count_args(line);
	if (!(args = ft_memalloc(sizeof(char *) * (args_numb + 1))))
		error_exit(sh, mem_alloc_err);
	while (numb < args_numb)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		args[numb] = ft_strnew(0);
		while (line[i] && !ft_isspace(line[i]))
			split_quotes(line, args, &i, numb);
		numb++;
	}
	return (args);
}
