/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_arrows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:12:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/03 19:54:41 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		up_arrow(char *buf, t_hist *hist, unsigned int *hist_counter)
{
	unsigned int	i;
	unsigned int	full_len;

	i = 0;
	full_len = 0;
	full_len = get_position(full_len);
	if (buf[5] == UP
		&& full_len == ft_strlen(g_info->line) + g_info->prompt_len + 1
		&& g_info->position >= (int)(g_info->win_width +
		g_info->prompt_len + 1))
		while (i++ < g_info->win_width)
			move_left();
//	if (buf[5] == UP &&
//		full_len > ft_strlen(g_info->line) + g_info->prompt_len + 1)
//		while (i++ < g_info->win_width)
//			move_left();
	else if (buf[2] == UP && hist && *hist_counter >= 1)
		print_prev_hist(hist, hist_counter);
}

void		down_arrow(char *buf, t_hist **hist, unsigned int *hist_counter)
{
	unsigned int	i;
	unsigned int	full_len;

	i = 0;
	full_len = 0;
	full_len = get_position(full_len);
	if (buf[5] == DOWN
		&& full_len == ft_strlen(g_info->line) + g_info->prompt_len + 1
		&& g_info->position - g_info->prompt_len - 1 + g_info->win_width
		<= (int)ft_strlen(g_info->line)
		&& g_info->line)
		while (i++ < g_info->win_width)
			move_right();
	else if (buf[2] == DOWN && *hist && *hist_counter <= g_info->hist_counter)
		print_next_hist(*hist, hist_counter);
}
