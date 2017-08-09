/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/09 20:45:07 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		*buffer = add_char(buf, *buffer, w);
	else
	{
		*buffer = ft_strjoin_free_first(*buffer, buf);
		ft_printf("%s", buf);
		if ((w->position + 1) % w->size == 0)
			ft_putchar('\n');
	}
	w->index++;
	w->position++;
	return (0);
}

static char	*parse_keys(char *buf, char *buffer, t_win *w)
{
	if (buf[2] == LEFT || buf[3] == LEFT || buf[2] == START)
		left_arrow(buf, buffer, w);
	else if (buf[2] == RIGHT || buf[3] == RIGHT || buf[2] == END)
		right_arrow(buf, buffer, w);
	else if (buf[2] == UP || buf[3] == UP)
		up_arrow(buf, buffer, w);
	else if (buf[2] == DOWN || buf[3] == DOWN)
		down_arrow(buf, buffer, w);
	else if ((buf[0] == BACKSPACE && w->index > 0) ||
			(buf[2] == DELETE && buffer[w->index]))
		buffer = del_char(buf, buffer, w);
	else if (buf[0] != BACKSPACE && buf[2] != DELETE)
			w->flag = check_print_position(buf, &buffer, w);
	return (buffer);
}

char		*read_line(t_win *w)
{
	char		*buffer;
	char		buf[8];

	if (!(buffer = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	w->position = w->prompt_len;
	w->index = 0;
	w->flag = 0;
	while (42)
	{
		ft_bzero(buf, 8);
		w->bytes = read(0, buf, 8);
//		if (buf[0] == '\033')
//		{
//			ft_bzero(buf, 8);
//			w->bytes = read(0, buf, 8);
//		}
	//	ft_printf("\nbytes = %d\n", w->bytes);
	//	if (w->bytes == 1 && (ft_isprint(buf[0]) || buf[0] == '\n'))
	//		if (check_print_position(buf, &buffer, w))
	//			return (buffer);
		buffer = parse_keys(buf, buffer, w);
		if (w->flag)
			return (buffer);
	}
}
