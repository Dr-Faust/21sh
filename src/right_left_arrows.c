/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_left_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:01:30 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 19:17:59 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		move_right(void)
{
	if ((g_info->position + 1) % g_info->win_size == 0)
		ft_putchar('\n');
	if ((g_info->position + 1) % g_info->win_size != 0)
		tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	g_info->line_index += g_info->bytes_str[g_info->bytes_index] - '0';
	g_info->position++;
	g_info->bytes_index++;
}

void		move_left(void)
{
	int		tmp;

//	ft_printf("\npos = %d\n", g_info->position);
//	ft_printf("line_ind = %d\n", g_info->line_index);
//	ft_printf("bytes_ind = %d\n", g_info->bytes_index);
	if (g_info->position % g_info->win_size != 0)
		tputs(tgetstr("le", 0), 1, &ft_put_my_char);
	if (g_info->position % g_info->win_size == 0)
	{
		ft_putstr("\033M");
		tmp = 0;
		while (tmp++ < g_info->win_size - 1)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
	g_info->line_index -= g_info->bytes_str[g_info->bytes_index - 1] - '0';
	g_info->position--;
	g_info->bytes_index--;
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
