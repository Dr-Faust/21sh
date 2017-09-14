/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/30 17:18:49 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_buf(char *buf)
{
	char		tmp[8];

	ft_bzero(buf, 8);
	g_info->bytes = read(0, buf, 1);
	ft_bzero(tmp, 8);
	if (buf[0] == '\033')
	{
		read(0, tmp, 8);
		ft_strcat(&buf[0], &tmp[0]);
	}
	else if (!ft_isascii(buf[0]))
		ft_bzero(buf, 8);
}

static void	init_struct(void)
{
	if (!g_info->line)
		if (!(g_info->line = ft_strnew(1)))
			error_exit(sh, mem_alloc_err);
	g_info->position = g_info->prompt_len + 1;
	g_info->line_index = 0;
}

static char	*manage_ret(char **ret)
{
	*ret = ft_strdup(g_info->line);
	ft_memdel((void **)&g_info->line);
	return (*ret);
}

char		*read_line(t_hist **hist)
{
	char		buf[8];
	char		*ret;
	int			flag;
	int			hist_counter;

	init_struct();
	while (42)
	{
		if (!g_info->line[0])
		{
			g_info->hist_search_flag = 1;
			hist_counter = g_info->hist_counter + 1;
		}
		flag = 0;
		ioctl(0, TIOCGWINSZ, &g_info->win);
		g_info->win_width = g_info->win.ws_col;
		g_info->win_height = g_info->win.ws_row;
		prompt_flag(42);
		manage_signals();
		read_buf(buf);
		parse_keys(buf, &flag, hist, &hist_counter);
		prompt_flag(21);
		if (flag)
			return (manage_ret(&ret));
	}
}
