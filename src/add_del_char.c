/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_del_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 19:26:48 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/18 21:06:47 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reprint_str_add(t_win *w, char *buf)
{
	char	*print;
	int		start;

	start = w->index;
	print = ft_strdup(buf);
	print = ft_strjoin_free(print, ft_strsub(g_line, start,
		ft_strlen(g_line) - start));
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	return (print);
}

char		*add_char(char *buf, t_win *w)
{
	char	*ret;
	int		start;
	char	*tmp;

	start = 0;
	ret = ft_strsub(g_line, start, w->index - start);
	ret = ft_strjoin_free(ret, reprint_str_add(w, buf));
	if (((int)ft_strlen(w->bytes_str) + w->prompt_len) % g_win_size == 0)
		tputs(tgetstr("up", 0), 1, &ft_put_my_char);
	if ((w->position + 1) % g_win_size == 0)
		ft_putchar('\n');
	start = 0;
	tmp = ft_strsub(w->bytes_str, start, w->i - start);
	tmp = ft_strjoin_free(tmp, ft_itoa(w->bytes));
	start = w->i;
	tmp = ft_strjoin_free(tmp, ft_strsub(w->bytes_str, start,
		ft_strlen(w->bytes_str) - start));
	ft_memdel((void **)&(w->bytes_str));
	w->bytes_str = ft_strdup(tmp);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&g_line);
	return (ret);
}

static void	reprint_str_del(t_win *w)
{
	char	*print;
	int		start;

	start = w->index + (w->bytes_str[w->i] - '0');
	print = ft_strsub(g_line, start, ft_strlen(g_line) - start);
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	ft_memdel((void **)&print);
}

char		*del_char(char *buf, t_win *w)
{
	char	*ret;
	int		start;
	char	*tmp;

	if (buf[0] == BACKSPACE && w->index > 0)
		move_left(w);
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	start = 0;
	tmp = ft_strsub(w->bytes_str, start, w->i - start);
	start = w->i + 1;
	tmp = ft_strjoin_free(tmp, ft_strsub(w->bytes_str, start,
		ft_strlen(w->bytes_str) - start));
	reprint_str_del(w);
	start = 0;
	ret = ft_strsub(g_line, start, w->index - start);
	start = w->index + (w->bytes_str[w->i] - '0');
	ret = ft_strjoin_free(ret, ft_strsub(g_line, start,
		ft_strlen(g_line) - start));
	ft_memdel((void **)&(w->bytes_str));
	w->bytes_str = ft_strdup(tmp);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&g_line);
	return (ret);
}
