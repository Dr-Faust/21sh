/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 12:02:16 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 16:52:44 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_quotes(int *flag, int quote, t_win *w)
{
	int		j;
	char	*str;

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
		g_quote_line = ft_strjoin_free_first(g_quote_line, str);
		j = -1;
		while (str[++j])
			if (str[j] == quote || !(ft_strcmp(g_quote_line, str)))
				*flag = 0;
		ft_memdel((void **)&str);
	}
}

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

static void	check_quotes(t_win *w)
{
	int		i;
	int		flag;

	i = 0;
	while (g_quote_line[i])
	{
		if ((g_quote_line[i] == 39 || g_quote_line[i] == 34) &&
			valid_quote(g_quote_line, i + 1, g_quote_line[i]) == -1)
		{
			flag = 1;
			print_quotes(&flag, g_quote_line[i], w);
		}
		else if ((g_quote_line[i] == 39 || g_quote_line[i] == 34) &&
				valid_quote(g_quote_line, i + 1, g_quote_line[i]) != -1)
		{
			i = valid_quote(g_quote_line, i + 1, g_quote_line[i]);
			i++;
		}
		else
			i++;
	}
}

char		*parse_quotes(char *line, t_win *w)
{
	char	*ret;

	g_quote_line = line;
	check_quotes(w);
	if (g_quote_line[ft_strlen(g_quote_line) - 1] == '\n')
	{
		ft_printf("here\n");
		g_quote_line[ft_strlen(g_quote_line) - 1] = '\0';
	}
	ret = ft_strdup(g_quote_line);
	ft_memdel((void **)&g_quote_line);
	return (ret);
}
