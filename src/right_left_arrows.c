/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_left_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:01:30 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/03 20:09:05 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		move_right(void)
{
	int		pos_diff;
	int		line_counter;

	if ((g_info->position) % g_info->win_width == 0 ||
		g_info->line[g_info->line_index] == '\n')
	{
		ft_putchar('\n');
		if (g_info->line[g_info->line_index] == '\n')
		{
			line_counter = g_info->position / g_info->win_width;
			pos_diff = g_info->position - (line_counter * g_info->win_width);
			g_info->position = g_info->position - pos_diff + g_info->win_width;
		}
	}
	else
		tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	g_info->line_index++;
	g_info->position++;
//	ft_printf("\npos = %d\n", g_info->position);
//	ft_printf("\nindx = %d\n", g_info->line_index);
}

void		move_left(void)
{
	int		tmp;
	
	if ((g_info->position - 1) % g_info->win_width == 0 ||
		g_info->line[g_info->line_index - 1] == '\n')
	{
		ft_putstr("\033M");
		if (g_info->line[g_info->line_index - 1] == '\n')
			extended_move_left(g_info->line_index - 1);
		else
		{
			tmp = 0;
			while (tmp++ < g_info->win_width - 1)
				tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
		}
	}
	else
		tputs(tgetstr("le", 0), 1, &ft_put_my_char);
	g_info->line_index--;
	g_info->position--;
//	ft_printf("\npos = %d\n", g_info->position);
//	ft_printf("\nindx = %d\n", g_info->line_index);
}

void		left_arrow(char *buf)
{
	if (buf[2] == LEFT && g_info->line_index > 0)
		move_left();
	else if (buf[3] == LEFT && g_info->line_index > 0)
	{
		while (g_info->line[g_info->line_index - 1] == ' ' &&
			g_info->line_index > 0)
			move_left();
		while (g_info->line[g_info->line_index - 1] != ' ' &&
			g_info->line_index > 0)
			move_left();
	}
	else if (buf[2] == START && g_info->line_index > 0)
		while (g_info->line_index > 0)
			move_left();
}

void		right_arrow(char *buf)
{
	if (buf[2] == RIGHT && g_info->line[g_info->line_index])
		move_right();
	else if (buf[3] == RIGHT && g_info->line[g_info->line_index])
	{
		while (g_info->line[g_info->line_index] != ' ' &&
			g_info->line_index < (int)ft_strlen(g_info->line))
			move_right();
		while (g_info->line[g_info->line_index] == ' ' &&
			g_info->line_index < (int)ft_strlen(g_info->line))
			move_right();
	}
	else if (buf[2] == END && g_info->line[g_info->line_index])
		while (g_info->line[g_info->line_index])
			move_right();
}
