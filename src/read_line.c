/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 17:28:00 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_print_position(char *buf, t_win *w)
{
	if (buf[0] == '\n')
	{
		while (g_line[w->index])
			move_right(w);
		ft_printf("\n");
		g_line = ft_strjoin_free_first(g_line, "\0");
		return (1);
	}
	else if (w->index < (int)ft_strlen(g_line))
		g_line = add_char(buf, w);
	else
	{
		w->bytes_str = ft_strjoin_free(w->bytes_str, ft_itoa(w->bytes));
		g_line = ft_strjoin_free_first(g_line, buf);
		ft_printf("%s", buf);
	}
	w->index += w->bytes_str[w->i] - '0';
	w->position++;
	w->i++;
	return (0);
}

static void	parse_keys(char *buf, t_win *w)
{
	if (buf[2] == LEFT || buf[3] == LEFT || buf[2] == START)
		left_arrow(buf, w);
	else if (buf[2] == RIGHT || buf[3] == RIGHT || buf[2] == END)
		right_arrow(buf, w);
	else if (buf[2] == UP || buf[3] == UP)
		up_arrow(buf, w);
	else if (buf[2] == DOWN || buf[3] == DOWN)
		down_arrow(buf, w);
	else if ((buf[0] == BACKSPACE && w->index > 0) ||
			(buf[3] == DELETE && g_line[w->index]))
		g_line = del_char(buf, w);
	else if (buf[0] != BACKSPACE && buf[3] != DELETE && !ft_strchr(buf, '\033'))
		w->flag = check_print_position(buf, w);
}

static void	read_buf(t_win *w, char *buf)
{
	char		tmp[8];

	ft_bzero(buf, 8);
	w->bytes = read(0, buf, 1);
	ft_bzero(tmp, 8);
	if (buf[0] == '\033')
	{
		read(0, tmp, 8);
		ft_strcat(&buf[0], &tmp[0]);
	}
	else if (!ft_isascii(buf[0]))
	{
		w->bytes += read(0, tmp, 1);
		ft_strcat(&buf[0], &tmp[0]);
	}
}

static void	init_struct(t_win *w)
{
	if (!(g_line = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	if (!(w->bytes_str = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	w->position = w->prompt_len;
	w->index = 0;
	w->flag = 0;
	w->i = 0;
}

char		*read_line(t_win *w)
{
	char		buf[8];
	char		*ret;

	init_struct(w);
	while (42)
	{
		ioctl(0, TIOCGWINSZ, &win_size);
		g_win_size = win_size.ws_col;
		prompt_flag(42);
		manage_signals();
		read_buf(w, buf);
		parse_keys(buf, w);
		prompt_flag(21);
		if (w->flag)
		{
			ret = ft_strdup(g_line);
			ft_memdel((void **)&g_line);
			ft_memdel((void **)&w->bytes_str);
			return (ret);
		}
	}
}
