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

void		up_arrow(char *buf, t_hist *hist, int *hist_counter)
{
	int		i;

	i = 0;
	if (buf[3] == UP && g_info->position >= g_info->win_size +
		g_info->prompt_len && g_info->line[g_info->line_index - 1])
		while (i++ < g_info->win_size)
			move_left();
	else if (buf[2] == UP && hist && *hist_counter >= 1)
	{
	/*	if (g_info->hist_search_flag)
		{
			g_info->hist_start_line = ft_strdup(g_info->line);
			g_info->hist_start_line_bytes = ft_strdup(g_info->bytes_str);
			g_info->hist_search_flag = 0;
		}*/
/*		if (*hist_counter > 1)
			*hist_counter -= 1;
		while (hist->id != *hist_counter)
		{
	//		ft_printf("\nhere\n");
			hist = hist->next;
	//		ft_printf("line = %s\n", hist->line);
		}*/
	//	if (!g_info->hist_start_line[0])
			print_prev_hist(hist, hist_counter);
	}
}

void		down_arrow(char *buf, t_hist **hist, int *hist_counter)
{
	int		i;

	i = 0;
	if (buf[3] == DOWN && g_info->position - g_info->prompt_len +
		g_info->win_size <= (int)ft_strlen(g_info->bytes_str) && g_info->line)
		while (i++ < g_info->win_size)
			move_right();
	else if (buf[2] == DOWN && *hist && *hist_counter <= g_info->hist_counter)
		print_next_hist(*hist, hist_counter);
}
