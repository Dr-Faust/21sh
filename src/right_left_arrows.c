/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_left_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:01:30 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/03 19:27:55 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		move_right(void)
{
	if ((g_info->position + 1) % g_info->win_size == 0 ||
		g_info->line[g_info->line_index] == '\n')
		ft_putchar('\n');
	if ((g_info->position + 1) % g_info->win_size != 0 &&
		g_info->line[g_info->line_index] != '\n')
		tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	g_info->line_index += g_info->bytes_str[g_info->bytes_index] - '0';
	g_info->position++;
	g_info->bytes_index++;
}

void		move_left(void)
{
	int		flag;
	int		line_indx;
	int		byte_indx;

	if (g_info->position % g_info->win_size != 0 &&
		g_info->line[g_info->line_index - 1] != '\n')
		tputs(tgetstr("le", 0), 1, &ft_put_my_char);
	if (g_info->position % g_info->win_size == 0 ||
		g_info->line[g_info->line_index - 1] == '\n')
	{
		ft_putstr("\033M");
		line_indx = 0;
		if (g_info->line[g_info->line_index - 1] == '\n')
		{
			flag = 0;
			line_indx = g_info->line_index - 2;
			byte_indx = g_info->bytes_index - 1;
			while (g_info->line[line_indx])
			{
				if (g_info->line[line_indx - 1] == '\n')
					flag = 1;
				line_indx -= g_info->bytes_str[byte_indx] - '0';
				byte_indx--;
			}
			if (!flag)
			{
				line_indx = g_info->line_index - 1;
				byte_indx = g_info->bytes_index - 2;
				while (line_indx > 0)
				{
					tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
					line_indx -= g_info->bytes_str[byte_indx] - '0';
					byte_indx--;
				}
				line_indx = 0;
				while (line_indx++ < g_info->prompt_len)
					tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
			}
			else
			{
				line_indx = g_info->line_index - 2;
				byte_indx = g_info->bytes_index - 2;
				while (g_info->line[line_indx] && g_info->line[line_indx] != '\n')
				{
					tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
					line_indx -= g_info->bytes_str[byte_indx] - '0';
					byte_indx--;
				}
			}
		}
		else
			while (line_indx++ < g_info->win_size - 1)
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
	if (buf[2] == RIGHT && g_info->line[g_info->line_index] &&
		g_info->bytes_str[g_info->bytes_index])
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
