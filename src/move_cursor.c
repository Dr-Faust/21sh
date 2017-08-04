/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 17:51:08 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/04 22:13:55 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		move_right(t_win *w, char *buf)
{
	int		count;

	if (w->position % (w->size - 1) == 0)
		ft_putchar('\n');
	tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	if ((buf[2] == RIGHT || buf[5] == RIGHT || buf[2] == END)
		&& (w->position + 1) % w->size == 0)
	{
		count = (w->position + 1) / w->size;
		while (count-- > 0)
			tputs(tgetstr("le", 0), 1, ft_put_my_char);
	}
	w->index++;
	w->position++;
}

void	move_left(t_win *w, char *buf)
{
	tputs(tgetstr("le", 0), 1, &ft_put_my_char);
	if (buf[0] != BACKSPACE && w->position % w->size == 0)
	{
		tputs(tgetstr("up", 0), 1, ft_put_my_char);
		w->position = 0;
		while (w->position++ < w->size - 1)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
	w->index--;
	w->position--;
}

void		left_side(char *buf, char *buffer, t_win *w)
{
	if (buf[2] == LEFT && w->index > 0)
		move_left(w, buf);
	else if (buf[5] == LEFT && w->index > 0)
	{
		while (buffer[w->index - 1] == ' ' && w->index > 0)
			move_left(w, buf);
		while (buffer[w->index - 1] != ' ' && w->index > 0)
			move_left(w, buf);
	}
	else if (buf[2] == START && w->index > 0)
		while (w->index > 0)
			move_left(w,buf);
}

void		right_side(char *buf, char *buffer, t_win *w)
{
	if (buf[2] == RIGHT && buffer[w->index])
		move_right(w, buf);
	else if (buf[5] == RIGHT && buffer[w->index])
	{
		while (buffer[w->index] != ' ' && w->index < (int)ft_strlen(buffer))
			move_right(w, buf);
		while (buffer[w->index] == ' ' && w->index < (int)ft_strlen(buffer))
			move_right(w, buf);
	}
	else if (buf[2] == END && buffer[w->index])
		while (buffer[w->index])
			move_right(w, buf);
}
