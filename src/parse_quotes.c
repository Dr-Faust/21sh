/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 12:02:16 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 20:31:44 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_quotes(int *flag, int quote)
{
	int		j;
	char	*str;

	while (*flag)
	{
		if (quote == 39)
		{
			g_info->prompt_len = 7;
			ft_printf("%s%s%s", YELLOW, "quote> ", DEF);
		}
		else if (quote == 34)
		{
			g_info->prompt_len = 8;
			ft_printf("%s%s%s", GREEN, "dquote> ", DEF);
		}
		str = read_line();
	//	ft_printf("str = %s\n", str);
		g_info->quote_line = ft_strjoin_free_first(g_info->quote_line, str);
		j = -1;
	//	ft_printf("line = %s\n", g_info->quote_line);
		while (str[++j])
			if (str[j] == quote || !(ft_strcmp(g_info->quote_line, str)))
				*flag = 0;
		if (!str[0] && !g_info->quote_line[0])
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

static void	check_quotes(void)
{
	int		i;
	int		flag;

	i = 0;
	while (g_info->quote_line[i])
	{
		if ((g_info->quote_line[i] == 39 || g_info->quote_line[i] == 34) &&
			valid_quote(g_info->quote_line, i + 1, g_info->quote_line[i]) == -1)
		{
			flag = 1;
			print_quotes(&flag, g_info->quote_line[i]);
		}
		else if ((g_info->quote_line[i] == 39 || g_info->quote_line[i] == 34) &&
				valid_quote(g_info->quote_line, i + 1, g_info->quote_line[i]) != -1)
		{
			i = valid_quote(g_info->quote_line, i + 1, g_info->quote_line[i]);
			i++;
		}
		else
			i++;
	}
}

char		*parse_quotes(char *line)
{
	char	*ret;

	g_info->quote_line = line;
	check_quotes();
//	if (g_info->quote_line[ft_strlen(g_info->quote_line) - 2] == '\n')
//	{
//		ft_printf("here\n");
//		g_info->quote_line[ft_strlen(g_info->quote_line) - 2] = '\0';
//	}
	ret = ft_strdup(g_info->quote_line);
	ft_memdel((void **)&g_info->quote_line);
	return (ret);
}
