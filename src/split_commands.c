/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:40:58 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/10 21:19:21 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			valid_quote(char *s, unsigned int i, char quote)
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

/*
**		i - index;
**		x.numb - amount of arguments in string;
**		x.start - start position for copping to new string;
**		x.flag - to know if we have already caught a quote.
*/

static void	split_quotes(char *line, char **args, unsigned int *i, t_var *x)
{
	while (line[*i] && !ft_isspace(line[*i]))
	{
		if ((line[*i] == 34 || line[*i] == 39) &&
				valid_quote(line, *i + 1, line[*i]) != -1)
		{
			x->start = *i + 1;
			*i = valid_quote(line, *i + 1, line[*i]);
			args[x->numb] = ft_strsub(line, x->start, (size_t)(*i - x->start));
			x->numb++;
			x->flag = 1;
			(*i)++;
		}
		else
			(*i)++;
	}
}

char		**split_command(char *line)
{
	char			**args;
	int				args_numb;
	unsigned int	i;
	t_var			x;

	i = 0;
	x.numb = 0;
	args_numb = count_args(line);
	if (!(args = ft_memalloc(sizeof(char *) * (args_numb + 1))))
		error_exit(mem_alloc_err);
	while (x.numb < args_numb)
	{
		x.flag = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		x.start = i;
		split_quotes(line, args, &i, &x);
		if (!x.flag)
			args[x.numb++] = ft_strsub(line, x.start, (size_t)(i - x.start));
	}
	return (args);
}
