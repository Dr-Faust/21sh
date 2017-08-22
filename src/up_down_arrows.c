/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_arrows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:12:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 19:19:01 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		up_arrow(char *buf)
{
	int		i;

	i = 0;
	if (buf[3] == UP && g_info->position >= g_info->win_size +
		g_info->prompt_len && g_info->line[g_info->line_index - 1])
		while (i++ < g_info->win_size)
			move_left();
}

void		down_arrow(char *buf)
{
	int		i;

	i = 0;
	if (buf[3] == DOWN && g_info->position - g_info->prompt_len +
		g_info->win_size <= (int)ft_strlen(g_info->bytes_str) && g_info->line)
		while (i++ < g_info->win_size)
			move_right();
}
