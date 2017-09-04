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

	flag = 0;
	counter = 0;
	line_indx = g_info->line_index - 1;
	byte_indx = g_info->bytes_index - 1;
	while (g_info->line[line_indx])
	{
		if (g_info->line[line_indx] == '\n')
			flag = 1;
		line_indx -= g_info->bytes_str[byte_indx--] - '0';
	}
	line_indx = g_info->line_index - 1;
	byte_indx = g_info->bytes_index - 1;
	while (g_info->line[line_indx] && g_info->line[line_indx] != '\n')
	{
		counter++;
		line_indx -= g_info->bytes_str[byte_indx--] - '0';
	}
	if (flag)
		g_info->position = g_info->position - counter + g_info->win_size - 1;
	else
		g_info->position = g_info->position - counter - g_info->prompt_len
			+ g_info->win_size;
}

/*void		extended_move_right(int line_indx, int byte_indx)
{
	int		flag;
	
	flag = 0;
	while (g_info->line[line_indx])
	{
		if (g_info->line[line_indx + 1] == '\n')
			flag = 1;
		line_indx += g_info->bytes_str[byte_indx++] - '0';
	}
	correct_position_right(line_indx, byte_indx, flag);
}*/

static void	correct_position_left(int line_indx, int byte_indx, int flag)
{
	int		counter;

	counter = 0;
	line_indx = g_info->line_index - 2;
	byte_indx = g_info->bytes_index - 2;
	if (!flag)
		while (line_indx > 0)
		{
			counter++;
			line_indx -= g_info->bytes_str[byte_indx--] - '0';
		}
	else
		while (g_info->line[line_indx] != '\n')
		{
			counter++;
			line_indx -= g_info->bytes_str[byte_indx--] - '0';
		}
	if (!flag)
		g_info->position = (g_info->position - g_info->win_size)
			+ counter + 1 + g_info->prompt_len;
	else
		g_info->position = (g_info->position - g_info->win_size) + counter + 1;
}

static void	move_left_till_new_line(int flag, int line_indx, int byte_indx)
{
	if (!flag)
	{
		correct_position_left(line_indx, byte_indx, flag);
		line_indx = g_info->line_index - 1;
		byte_indx = g_info->bytes_index - 2;
		while (line_indx > 0)
		{
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
			line_indx -= g_info->bytes_str[byte_indx--] - '0';
		}
		line_indx = 0;
		while (line_indx++ < g_info->prompt_len)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}
	else
	{
		correct_position_left(line_indx, byte_indx, flag);
		line_indx = g_info->line_index - 2;
		byte_indx = g_info->bytes_index - 2;
		while (g_info->line[line_indx] && g_info->line[line_indx] != '\n')
		{
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
			line_indx -= g_info->bytes_str[byte_indx--] - '0';
		}
	}
}

void		extended_move_left(void)
{
	int		flag;
	int		line_indx;
	int		byte_indx;

	flag = 0;
	line_indx = g_info->line_index - 2;
	byte_indx = g_info->bytes_index - 1;
	while (g_info->line[line_indx])
	{
		if (g_info->line[line_indx - 1] == '\n')
			flag = 1;
		line_indx -= g_info->bytes_str[byte_indx--] - '0';
	}
	move_left_till_new_line(flag, line_indx, byte_indx);
}
