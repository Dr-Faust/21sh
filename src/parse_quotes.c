/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 12:02:16 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/10 21:19:14 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_quotes(char **line, int *i, char quote)
{
	char	*str;
	int		j;
	int		flag;

	flag = 0;
	*line = ft_strjoin_free_first(*line, "\n");
	while (42)
	{
		if (quote == 39)
			ft_printf("quote> ");
		else if (quote == 34)
			ft_printf("dquote> ");
		str = read_line();
		str = ft_strjoin_free_first(str, "\n");
		*line = ft_strjoin_free_first(*line, str);
		j = -1;
		while (str[++j])
			if (str[j] == quote)
				flag = 1 ;
	//	ft_printf("STR = %s\n", str);
		ft_memdel((void **)&str);
		if (flag)
			break ;
	}
	*i = ft_strlen(*line);
}
