/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_left_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:01:30 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/17 14:56:50 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		move_right(t_win *w)
{
	if ((w->position + 1) % g_win_size == 0)
		ft_putchar('\n');
	if ((w->position + 1) % g_win_size != 0)
		tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	w->index += w->bytes_str[w->i] - '0';
	w->position++;
	w->i++;
}

void		move_left(t_win *w)
{
	int		tmp;

	if (w->position % g_win_size != 0)
		tputs(tgetstr("le", 0), 1, &ft_put_my_char);
	if (w->position % g_win_size == 0)
	{
		ft_putstr("\033M");
	//	tputs(tgetstr("sr", 0), 1, ft_put_my_char);
		tmp = 0;
		while (tmp++ < g_win_size - 1)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
	w->index -= w->bytes_str[w->i - 1] - '0';
	w->position--;
	w->i--;
}

void		left_arrow(char *buf, char *buffer, t_win *w)
{
	if (buf[2] == LEFT && w->index > 0)
		move_left(w);
	else if (buf[3] == LEFT && w->index > 0)
	{
		while (buffer[w->index - 1] == ' ' && w->index > 0)
			move_left(w);
		while (buffer[w->index - 1] != ' ' && w->index > 0)
			move_left(w);
	}
	else if (buf[2] == START && w->index > 0)
		while (w->index > 0)
			move_left(w);
}

void		right_arrow(char *buf, char *buffer, t_win *w)
{
	if (buf[2] == RIGHT && buffer[w->index])
		move_right(w);
	else if (buf[3] == RIGHT && buffer[w->index])
	{
		while (buffer[w->index] != ' ' && w->index < (int)ft_strlen(buffer))
			move_right(w);
		while (buffer[w->index] == ' ' && w->index < (int)ft_strlen(buffer))
			move_right(w);
	}
	else if (buf[2] == END && buffer[w->index])
		while (buffer[w->index])
			move_right(w);
}
