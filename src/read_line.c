/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/17 21:31:26 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_buf(char *buf, char *buffer, int *i)
{
	if (buf[2] == 'C' && buffer[(*i)])
	{
		ft_printf("%s", buf);
		(*i)++;
	}
	else if (buf[2] == 'D' && (*i) > 0)
	{
		ft_printf("%s", buf);
		(*i)--;
	}
/*	else if (buf[2] == 'H' && (*i) > 0)
	{
		ft_printf("%s", buf);
		*i = 0;
	}
	else if (buf[2] == 'F' && buffer[(*i)])
	{
		ft_printf("%s", buf);
		*i = ft_strlen(buffer) - 1;
	}
	ft_printf("%s", buf);*/
}

char		*read_line(void)
{
	char	*buffer;
	char	buf[8];
	int		i;

	if (!(buffer = ft_strnew(1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (42)
	{
		ft_bzero(buf, 8);
		read(0, buf, 8);
		if ((ft_isprint(buf[0]) || buf[0] == '\n') && !buf[1])
		{
			i++;
			buffer = ft_strjoin_free_first(buffer, buf);
			ft_printf("%c", buf[0]);
			if (buf[0] == '\n')
				return (buffer = ft_strjoin_free_first(buffer, "\0"));
		}
		else
			parse_buf(buf, buffer, &i);
	}
}
