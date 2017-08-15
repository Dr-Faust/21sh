/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_arrows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:12:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/15 18:50:06 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		up_arrow(char *buf, char *buffer, t_win *w)
{
	int		i;

	i = 0;
	if (buf[3] == UP && w->position >= w->size + w->prompt_len &&
		buffer[w->index - 1])
		while (i++ < w->size)
			move_left(w);
}

void		down_arrow(char *buf, char *buffer, t_win *w)
{
	int		i;

	i = 0;
	if (buf[3] == DOWN &&
		w->position - w->prompt_len + w->size <= (int)ft_strlen(w->bytes_str) &&
		buffer)
		while (i++ < w->size)
			move_right(w);
}
