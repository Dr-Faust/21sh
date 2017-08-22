/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_del_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 19:26:48 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 19:21:48 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reprint_str_add(char *buf)
{
	char	*print;
	int		start;

	start = g_info->line_index;
	print = ft_strdup(buf);
	print = ft_strjoin_free(print, ft_strsub(g_info->line, start,
		ft_strlen(g_info->line) - start));
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	return (print);
}

char		*add_char(char *buf)
{
	char	*ret;
	int		start;
	char	*tmp;

	start = 0;
	ret = ft_strsub(g_info->line, start, g_info->line_index - start);
	ret = ft_strjoin_free(ret, reprint_str_add(buf));
	if (((int)ft_strlen(g_info->bytes_str) + g_info->prompt_len) %
		g_info->win_size == 0)
		tputs(tgetstr("up", 0), 1, &ft_put_my_char);
	if ((g_info->position + 1) % g_info->win_size == 0)
		ft_putchar('\n');
	start = 0;
	tmp = ft_strsub(g_info->bytes_str, start, g_info->bytes_index - start);
	tmp = ft_strjoin_free(tmp, ft_itoa(g_info->bytes));
	start = g_info->bytes_index;
	tmp = ft_strjoin_free(tmp, ft_strsub(g_info->bytes_str, start,
		ft_strlen(g_info->bytes_str) - start));
	ft_memdel((void **)&(g_info->bytes_str));
	g_info->bytes_str = ft_strdup(tmp);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&g_info->line);
	return (ret);
}

static void	reprint_str_del(void)
{
	char	*print;
	int		start;

	start = g_info->line_index + (g_info->bytes_str[g_info->bytes_index] - '0');
	print = ft_strsub(g_info->line, start, ft_strlen(g_info->line) - start);
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	ft_memdel((void **)&print);
}

char		*del_char(char *buf)
{
	char	*ret;
	int		start;
	char	*tmp;

	if (buf[0] == BACKSPACE && g_info->line_index > 0)
		move_left();
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	start = 0;
	tmp = ft_strsub(g_info->bytes_str, start, g_info->bytes_index - start);
	start = g_info->bytes_index + 1;
	tmp = ft_strjoin_free(tmp, ft_strsub(g_info->bytes_str, start,
		ft_strlen(g_info->bytes_str) - start));
	reprint_str_del();
	start = 0;
	ret = ft_strsub(g_info->line, start, g_info->line_index - start);
	start = g_info->line_index + (g_info->bytes_str[g_info->bytes_index] - '0');
	ret = ft_strjoin_free(ret, ft_strsub(g_info->line, start,
		ft_strlen(g_info->line) - start));
	ft_memdel((void **)&(g_info->bytes_str));
	g_info->bytes_str = ft_strdup(tmp);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&g_info->line);
	return (ret);
}
