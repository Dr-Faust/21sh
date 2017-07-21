/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/21 17:32:47 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_keys(char *buf, char *buffer, int *position)
{
	if (buf[2] == RIGHT && buffer[(*position)])
	{
		ft_putstr(tgetstr("nd", 0));
		(*position)++;
	}
	else if (buf[2] == LEFT && (*position) > 0)
	{
		ft_putstr(tgetstr("le", 0));
		(*position)--;
	}
	else if ((buf[0] == BACKSPACE && (*position) > 0) ||
			(buf[2] == DELETE && buffer[(*position)]))
		buffer = del_char(buf, buffer, position); 
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
	return (buffer);
}

static int	check_print_position(char *buf, char **buffer, int *position)
{
	if (buf[0] == '\n')
	{
		ft_printf("\n");
		*buffer = ft_strjoin_free_first(*buffer, "\n\0");
		return (1);
	}
	else if ((*position) < (int)ft_strlen(*buffer))
		*buffer = add_char(buf[0], *buffer, position);
	else
	{
		*buffer = ft_strjoin_free_first(*buffer, buf);
		ft_printf("%c", buf[0]);
	}
	(*position)++;
	return (0);
}

char		*read_line(void)
{
	char		*buffer;
	char		buf[8];
	int			position;
	int			bytes;

	if (!(buffer = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	position = 0;
	while (42)
	{
		ft_bzero(buf, 8);
		bytes = read(0, buf, 8);
		if (bytes == 1 && (ft_isprint(buf[0]) || buf[0] == '\n'))
			if (check_print_position(buf, &buffer, &position))
				return (buffer);
		buffer = parse_keys(buf, buffer, &position);
	}
}
