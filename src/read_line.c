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

static int	check_print_position(char *buf)
{
	if (buf[0] == '\n')
	{
		while (g_info->line[g_info->line_index])
			move_right();
		ft_printf("\n");
		g_info->line = ft_strjoin_free_first(g_info->line, "\n\0");
		return (1);
	}
	else if (g_info->line_index < (int)ft_strlen(g_info->line))
		g_info->line = add_char(buf);
	else
	{
		g_info->bytes_str = ft_strjoin_free(g_info->bytes_str,
			ft_itoa(g_info->bytes));
		g_info->line = ft_strjoin_free_first(g_info->line, buf);
		ft_printf("%s", buf);
	}
	g_info->line_index += g_info->bytes_str[g_info->bytes_index] - '0';
	g_info->position++;
	g_info->bytes_index++;
	return (0);
}

static void	parse_keys(char *buf, int *flag, t_hist **hist, int *hist_counter)
{
	if (buf[2] == LEFT || buf[3] == LEFT || buf[2] == START)
		left_arrow(buf);
	else if (buf[2] == RIGHT || buf[3] == RIGHT || buf[2] == END)
		right_arrow(buf);
	else if (buf[2] == UP || buf[3] == UP)
		up_arrow(buf, *hist, hist_counter);
	else if (buf[2] == DOWN || buf[3] == DOWN)
		down_arrow(buf, hist, hist_counter);
	else if ((buf[0] == BACKSPACE && g_info->line_index > 0) ||
			(buf[3] == DELETE && g_info->line[g_info->line_index]))
		g_info->line = del_char(buf);
	else if (buf[0] == CTRL_D && !g_info->line[0])
	{
		*flag = 1;
		g_info->line = ft_strjoin_free_first(g_info->line, "exit");
		ft_putchar('\n');
	}
	else if (buf[0] != BACKSPACE && buf[3] != DELETE && !ft_isunprint(buf[0]))
		*flag = check_print_position(buf);
}

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
	{
		g_info->bytes += read(0, tmp, 1);
		ft_strcat(&buf[0], &tmp[0]);
	}
}

static void	init_struct(int *hist_counter)
{
	if (!g_info->line)
		if (!(g_info->line = ft_strnew(1)))
			error_exit(sh, mem_alloc_err);
	if (!g_info->bytes_str)
		if (!(g_info->bytes_str = ft_strnew(1)))
			error_exit(sh, mem_alloc_err);
	if (!g_info->bytes_quote_str)
		if (!(g_info->bytes_quote_str = ft_strnew(1)))
			error_exit(sh, mem_alloc_err);
	g_info->position = g_info->prompt_len;
	g_info->line_index = 0;
	g_info->bytes_index = 0;
	*hist_counter = g_info->hist_counter + 1;
}

char		*read_line(t_hist **hist)
{
	char		buf[8];
	char		*ret;
	int			flag;
	int			hist_counter;

	init_struct(&hist_counter);
	while (42)
	{
		flag = 0;
		ioctl(0, TIOCGWINSZ, &g_info->win);
		g_info->win_size = g_info->win.ws_col;
		prompt_flag(42);
		manage_signals();
		read_buf(buf);
		parse_keys(buf, &flag, hist, &hist_counter);
		prompt_flag(21);
		if (flag)
		{
			ret = ft_strdup(g_info->line);
			g_info->bytes_quote_str = ft_strjoin_free_first(g_info->bytes_quote_str, g_info->bytes_str);
			ft_memdel((void **)&g_info->line);
			ft_memdel((void **)&g_info->bytes_str);
			return (ret);
		}
	}
}
