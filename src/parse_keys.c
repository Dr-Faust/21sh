/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:53:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/03 19:53:58 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_print_position(char *buf)
{
	if (buf[0] == '\n')
	{
		while (g_info->line[g_info->index])
			move_right();
		ft_printf("\n");
		g_info->line = ft_strjoin_free_first(g_info->line, "\n\0");
		return (1);
	}
	else if (g_info->index < (unsigned int)ft_strlen(g_info->line))
		g_info->line = add_char(buf);
	else
	{
		g_info->line = ft_strjoin_free_first(g_info->line, buf);
		ft_printf("%s", buf);
		if (g_info->position % g_info->win_width == 0)
		{
			ft_putchar('a');
			tputs(tgetstr("le", 0), 1, &ft_put_my_char);
			tputs(tgetstr("dc", 0), 1, &ft_put_my_char);
		}
	}
	g_info->index++;
	g_info->position++;
	return (0);
}

void		parse_keys(char *buf, bool *flag, t_hist **hist, unsigned int *hist_counter)
{
	if (buf[2] == LEFT || buf[3] == LEFT || buf[2] == START)
		left_arrow(buf);
	else if (buf[2] == RIGHT || buf[3] == RIGHT || buf[2] == END)
		right_arrow(buf);
	else if (buf[2] == UP || buf[5] == UP)
		up_arrow(buf, *hist, hist_counter);
	else if (buf[2] == DOWN || buf[5] == DOWN)
		down_arrow(buf, hist, hist_counter);
	else if ((buf[0] == BACKSPACE && g_info->index > 0) ||
			(buf[3] == DELETE && g_info->line[g_info->index]))
		g_info->line = del_char(buf);
	else if (buf[0] == CTRL_D && !g_info->line[0])
	{
		*flag = true;
		g_info->line = ft_strjoin_free_first(g_info->line, "exit");
		ft_putchar('\n');
	}
	else if (buf[0] != BACKSPACE && buf[3] != DELETE &&
			!ft_isunprint(buf[0]))
		*flag = check_print_position(buf);
}
