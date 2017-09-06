/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_move_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:37:43 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/03 20:09:10 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		extended_move_right(int line_indx)
{
	int		counter;
	int		flag;

	flag = 0;
	counter = 0;
	while (line_indx--)
		if (g_info->line[line_indx] == '\n')
			flag = 1;
	line_indx = g_info->line_index - 1;
/*	if (!flag)
		while (--line_indx > 0)
			counter++;
	else
	{
		while (g_info->line[--line_indx] != '\n')
			counter++;
	}*/
	while (g_info->line[line_indx] && g_info->line[line_indx] != '\n')
	{
		counter++;
		line_indx--;
	}
	if (counter >= g_info->win_size)
		counter %= g_info->win_size;
	if (flag)
		g_info->position = g_info->position - counter + g_info->win_size - 1;
	else
		g_info->position = g_info->position - counter - g_info->prompt_len
			+ g_info->win_size;
}

static int	correct_position_left(int flag, int line_indx)
{
	int		counter;

	counter = 0;
	if (!flag)
	{
		ft_printf("\nhere_1\n");
		while (--line_indx > 0)
			counter++;
	}
	else
	{
//		ft_printf("\nhere_2\n");
		while (g_info->line[--line_indx] != '\n')
			counter++;
	}
	if (counter >= g_info->win_size)
			counter %= g_info->win_size;
	ft_printf("\nconter = %d\n", counter);
	if (!flag)
		g_info->position = (g_info->position - g_info->win_size)
			+ counter + g_info->prompt_len + 1;
	else
		g_info->position = (g_info->position - g_info->win_size) + counter + 1;
	return (counter);
}

static void	move_left_till_new_line(int flag, int line_indx)
{
	int		counter;

	if (!flag)
	{
		counter = correct_position_left(flag, line_indx);
		while (counter-- > 0)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
		while (counter++ < g_info->prompt_len)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
	else
	{
		counter = correct_position_left(flag, line_indx);
		while (counter-- > 0)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
}

void		extended_move_left(int line_indx)
{
	int		flag;

	flag = 0;
	while (--line_indx)
		if (g_info->line[line_indx] == '\n')
			flag = 1;
	move_left_till_new_line(flag, g_info->line_index - 1);
}
