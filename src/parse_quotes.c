/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 12:02:16 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/17 18:15:07 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_quotes(char **line, int *flag, int quote, t_win *w)
{
	char	*str;
	int		j;

	while (*flag)
	{
		if (quote == 39)
		{
			w->prompt_len = 7;
			ft_printf("quote> ");
		}
		else if (quote == 34)
		{
			w->prompt_len = 8;
			ft_printf("dquote> ");
		}
		str = read_line(w);
		*line = ft_strjoin_free_first(*line, str);
		j = -1;
		while (str[++j])
			if (str[j] == quote)
				*flag = 0;
		ft_memdel((void **)&str);
	}
}

char		*parser(char *line, t_win *w)
{
	int		flag;
	int		i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == 39 || line[i] == 34) &&
			valid_quote(line, i + 1, line[i]) == -1)
		{
			flag = 1;
			print_quotes(&line, &flag, line[i], w);
		}
		else if ((line[i] == 39 || line[i] == 34) &&
				valid_quote(line, i + 1, line[i]) != -1)
		{
			i = valid_quote(line, i + 1, line[i]);
			i++;
		}
		else
			i++;
	}
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}
