/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_arrows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:12:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/08 21:04:51 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		up_arrow(char *buf, char *buffer, t_win *w)
{
	if (buf[3] == UP && w->position >= w->size + w->prompt_len &&
		buffer[w->index - 1])
	{
		tputs(tgetstr("up", 0), 1, &ft_put_my_char);
		w->position -= w->size;
		w->index -= w->size;
	}
}

void		down_arrow(char *buf, char *buffer, t_win *w)
{
	if (buf[3] == DOWN && w->position < (int)ft_strlen(buffer) &&
		w->position > w->prompt_len && buffer[w->index])
	{
		tputs(tgetstr("do", 0), 1, &ft_put_my_char);
		w->position += w->size;
		w->index += w->size;
	}
}
