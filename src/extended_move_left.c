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

void		extended_move_right(int line_indx, int byte_indx)
{
	int		counter;
	int		flag;
	int		line_indx_1;
	int		byte_indx_1;

	flag = 0;
	counter = 0;
	line_indx -= g_info->bytes_str[byte_indx] - '0';
	line_indx_1 = line_indx;
	byte_indx_1 = byte_indx;
	while (g_info->line[line_indx])
	{
		if (g_info->line[line_indx] == '\n')
			flag = 1;
		line_indx -= g_info->bytes_str[byte_indx--] - '0';
	}
	while (g_info->line[line_indx_1] && g_info->line[line_indx_1] != '\n')
	{
		counter++;
		line_indx_1 -= g_info->bytes_str[byte_indx_1--] - '0';
	}
	if (counter > g_info->win_size)
		counter %= g_info->win_size;
	if (flag)
		g_info->position = g_info->position - counter + g_info->win_size - 1;
	else
		g_info->position = g_info->position - counter - g_info->prompt_len
			+ g_info->win_size;
}

static int	correct_position_left(int line_indx, int byte_indx, int flag)
{
	int		counter;

	counter = 0;
	line_indx -= (g_info->bytes_str[byte_indx--] - '0');
	if (!flag)
		while (line_indx > 0)
		{
			counter++;
			line_indx -= g_info->bytes_str[byte_indx--] - '0';
		}
	else
	{
		while (g_info->line[line_indx] != '\n')
		{
			counter++;
			line_indx -= g_info->bytes_str[byte_indx--] - '0';
		}
		if (counter > g_info->win_size)
			counter %= g_info->win_size;
	}
	if (!flag)
		g_info->position = (g_info->position - g_info->win_size)
			+ counter + 1 + g_info->prompt_len;
	else
		g_info->position = (g_info->position - g_info->win_size) + counter + 1;
	return (counter);
}

static void	move_left_till_new_line(int flag, int line_indx, int byte_indx)
{
	int		counter;

	if (!flag)
	{
		counter = correct_position_left(line_indx, byte_indx, flag);
		while (counter-- > 0)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
		while (counter++ < g_info->prompt_len)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
	else
	{
		counter = correct_position_left(line_indx, byte_indx, flag);
		while (counter-- > 0)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
}

void		extended_move_left(int line_indx, int byte_indx)
{
	int		flag;
	int		copy_byte_indx;
	int		copy_line_indx;

	flag = 0;
	copy_line_indx = line_indx;
	copy_byte_indx = byte_indx;
	while (g_info->line[line_indx])
	{
		line_indx -= g_info->bytes_str[byte_indx--] - '0';
		if (g_info->line[line_indx] == '\n')
			flag = 1;
	}
	move_left_till_new_line(flag, copy_line_indx, copy_byte_indx);
}
