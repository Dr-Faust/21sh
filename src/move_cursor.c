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

static void	check_term_len_right(t_win *w, char *buf)
{
	if (w->position == w->size - 1)
		ft_putchar('\n');
	tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	if ((buf[2] == RIGHT || buf[3] == RIGHT || buf[2] == END)
		&& w->position == w->size - 1)
		tputs(tgetstr("le", 0), 1, ft_put_my_char);
	w->index++;
	w->position++;
}

static void	check_term_len_left(t_win *w)
{
	tputs(tgetstr("le", 0), 1, &ft_put_my_char);
	if (w->position == w->size)
	{
		tputs(tgetstr("up", 0), 1, ft_put_my_char);
		w->position = 0;
		while (w->position++ < w->size - 1)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
	w->index--;
	w->position--;
}

void		move_left(char *buf, char *buffer, t_win *w)
{
	if (buf[2] == LEFT && w->index > 0)
		check_term_len_left(w);
	else if (buf[3] == LEFT && w->index > 0)
	{
		while (buffer[w->index - 1] == ' ' && w->index > 0)
			check_term_len_left(w);
		while (buffer[w->index - 1] != ' ' && w->index > 0)
			check_term_len_left(w);
	}
	else if (buf[2] == START && w->index > 0)
		while (w->index > 0)
			check_term_len_left(w);
}

void		move_right(char *buf, char *buffer, t_win *w)
{
	if (buf[2] == RIGHT && buffer[w->index])
		check_term_len_right(w, buf);
	else if (buf[3] == RIGHT && buffer[w->index])
	{
		while (buffer[w->index] != ' ' && w->index < (int)ft_strlen(buffer))
			check_term_len_right(w, buf);
		while (buffer[w->index] == ' ' && w->index < (int)ft_strlen(buffer))
			check_term_len_right(w, buf);
	}
	else if (buf[2] == END && buffer[w->index])
		while (buffer[w->index])
			check_term_len_right(w, buf);
}
