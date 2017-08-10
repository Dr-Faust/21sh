/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/10 21:11:27 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_print_position(char *buf, char **buffer, t_win *w)
{
	char	*tmp;

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
		*buffer = add_char(buf, *buffer, w);
	else
	{
		*buffer = ft_strjoin_free_first(*buffer, buf);
		ft_printf("%s", buf);
		if ((w->position + 1) % w->size == 0)
			ft_putchar('\n');
	}
	w->index += w->bytes[w->i] - '0';
	w->position++;
	w->i++;
	return (0);
}

static char	*parse_keys(char *buf, char *buffer, t_win *w)
{
	if (buf[2] == LEFT || buf[5] == LEFT || buf[2] == START)
		left_arrow(buf, buffer, w);
	else if (buf[2] == RIGHT || buf[5] == RIGHT || buf[2] == END)
		right_arrow(buf, buffer, w);
	else if (buf[2] == UP || buf[5] == UP)
		up_arrow(buf, buffer, w);
	else if (buf[2] == DOWN || buf[5] == DOWN)
		down_arrow(buf, buffer, w);
	else if ((buf[0] == BACKSPACE && w->index > 0) ||
			(buf[3] == DELETE && buffer[w->index]))
		buffer = del_char(buf, buffer, w);
	else if (buf[0] != BACKSPACE && buf[3] != DELETE && !ft_strchr(buf, '\033'))
			w->flag = check_print_position(buf, &buffer, w);
	return (buffer);
}

static void	read_buf(t_win *w, char *buf)
{
	char		tmp[8];
	int			bytes;

	bytes = read(0, buf, 1);
	ft_bzero(tmp, 8);
	if (buf[0] == '\033')
	{
		read(0, tmp, 8);
		ft_strcat(&buf[0], &tmp[0]);
	}
	else if (!ft_isascii(buf[0]))
	{
		bytes += read(0, tmp, 4);
		ft_strcat(&buf[0], &tmp[0]);
	}
	w->bytes = ft_strjoin_free_first(w->bytes, ft_itoa(bytes));
}

char		*read_line(t_win *w)
{
	char		*buffer;
	char		buf[8];

	if (!(buffer = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	if (!(w->bytes = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	w->position = w->prompt_len;
	w->index = 0;
	w->flag = 0;
	w->i = 0;
	while (42)
	{
		ft_bzero(buf, 8);
		read_buf(w, buf);
		buffer = parse_keys(buf, buffer, w);
		if (w->flag)
			return (buffer);
	}
}
