/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_move_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:37:43 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/14 15:27:37 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	correct_position_left(bool flag, unsigned int line_indx)
{
	unsigned int	counter;
	unsigned int	line_counter;

	counter = 0;
	if (!flag)
	{
		line_indx += g_info->prompt_len;
		line_counter = line_indx / g_info->win_width;
		while (line_indx-- > (g_info->win_width * line_counter))
			counter++;
	}
	else
		while (g_info->line[--line_indx] != '\n')
			counter++;
	if (counter >= g_info->win_width)
		counter %= g_info->win_width;
	g_info->position = (g_info->position - g_info->win_width) + counter + 1;
	return (counter);
}

void		extended_move_left(unsigned int line_indx)
{
	bool			flag;
	unsigned int	counter;

	flag = 0;
	while (--line_indx)
		if (g_info->line[line_indx] == '\n')
			flag = 1;
	line_indx = g_info->index - 1;
	counter = correct_position_left(flag, line_indx);
	while (counter-- > 0)
		tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
}
