/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_arrows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:12:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 15:05:56 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		up_arrow(char *buf, t_win *w)
{
	int		i;

	i = 0;
	if (buf[3] == UP && w->position >= g_win_size + w->prompt_len &&
		g_line[w->index - 1])
		while (i++ < g_win_size)
			move_left(w);
}

void		down_arrow(char *buf, t_win *w)
{
	int		i;

	i = 0;
	if (buf[3] == DOWN &&
		w->position - w->prompt_len + g_win_size <= (int)ft_strlen(w->bytes_str)
		&& g_line)
		while (i++ < g_win_size)
			move_right(w);
}
