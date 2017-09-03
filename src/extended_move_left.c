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

static void	move_left_till_new_line(int flag, int line_indx, int byte_indx)
{
	if (!flag)
	{
		ft_printf("\nhere_1\n");
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
		ft_printf("\nhere_2\n");
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
