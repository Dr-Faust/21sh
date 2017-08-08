/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/08 20:44:41 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_keys(char *buf, char *buffer, t_win *w)
{
	if ((buf[2] == LEFT || buf[3] == LEFT || buf[2] == START)
		&& w->index > 0)
		left_arrow(buf, buffer, w);
	else if ((buf[2] == RIGHT || buf[3] == RIGHT || buf[2] == END)
			&& buffer[w->index])
		right_arrow(buf, buffer, w);
	else if ((buf[2] == UP || buf[3] == UP) && w->position > w->size)
		up_arrow(buf, buffer, w);
	else if ((buf[2] == DOWN || buf[3] == DOWN) && w->position <= w->size)
		down_arrow(buf, buffer, w);
	else if ((buf[0] == BACKSPACE && w->index > 0) ||
			(buf[2] == DELETE && buffer[w->index]))
		buffer = del_char(buf, buffer, w);
	return (buffer);
}

static int	check_print_position(char *buf, char **buffer, t_win *w)
{
	char *tmp;

	tmp = *buffer;
	if (buf[0] == '\n')
	{
		while (tmp[w->index])
			move_right(w);
		ft_printf("\n");
		*buffer = ft_strjoin_free_first(*buffer, "\n\0");
		return (1);
	}
	else if (w->index < (int)ft_strlen(*buffer))
		*buffer = add_char(buf[0], *buffer, w);
	else
	{
		*buffer = ft_strjoin_free_first(*buffer, buf);
		ft_printf("%c", buf[0]);
		if ((w->position + 1) % w->size == 0)
			ft_putchar('\n');
	}
	w->index++;
	w->position++;
	return (0);
}

char		*read_line(t_win *w)
{
	char		*buffer;
	char		buf[8];
	int			bytes;

	if (!(buffer = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	w->position = w->prompt_len;
	w->index = 0;
	while (42)
	{
		ft_bzero(buf, 8);
		bytes = read(0, buf, 8);
		if (bytes == 1 && (ft_isprint(buf[0]) || buf[0] == '\n'))
			if (check_print_position(buf, &buffer, w))
				return (buffer);
		buffer = parse_keys(buf, buffer, w);
	}
}
