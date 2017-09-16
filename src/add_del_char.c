/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_del_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 19:26:48 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/14 21:12:23 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned short	rows_till_lower_bound(unsigned int indx)
{
	unsigned int	position;
	unsigned int	full_len;
//	unsigned int	len;
	unsigned short	rows;

	rows = 0;
	position = g_info->position;
//	ft_printf("\npos = %d\n", position);
	full_len = get_position(indx);
//	ft_printf("\nfull_len = %d\n", full_len);
	while (position++ < full_len)
		if (position % g_info->win_width == 0)
			rows++;
//	ft_printf("\nlen = %d\n", len);
//	rows = (len / g_info->win_width);
//	ft_printf("\nrows = %d\n", rows);
	return (rows);
}

static char				*reprint_str_add(char *buf)
{
	char	*print;
	int		start;

	start = g_info->index;
	print = ft_strdup(buf);
	print = ft_strjoin_free(print, ft_strsub(g_info->line, start,
		ft_strlen(g_info->line) - start));
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	return (print);
}

char					*add_char(char *buf)
{
	char			*ret;
	unsigned int	indx;
	unsigned short	rows_till_bound;

	indx = g_info->index;
	ret = ft_strsub(g_info->line, 0, g_info->index);
	ret = ft_strjoin_free(ret, reprint_str_add(buf));
	while (g_info->line[indx])
	{
		if (g_info->line[indx] == '\n')
			break ;
		indx++;
	}
	indx -= g_info->index;
	rows_till_bound = rows_till_lower_bound(indx);
//ft_printf("\nrows = %d\n", rows_till_bound);
//	ft_printf("\npos = %d\n", g_info->row_position);
	if ((g_info->position) % g_info->win_width == 0)
	{
		if (g_info->row_position < g_info->win_height)
			g_info->row_position++;
		ft_putchar('\n');
	}
	if (g_info->row_position >= (g_info->win_height - rows_till_bound) &&
		g_info->row_position <= g_info->win_height)
		if ((g_info->position + indx - 1) % g_info->win_width == 0)
			tputs(tgetstr("up", 0), 1, &ft_put_my_char);
	ft_memdel((void **)&g_info->line);
	return (ret);
}

static void				reprint_str_del(void)
{
	char	*print;
	int		start;

	start = g_info->index + 1;
	print = ft_strsub(g_info->line, start, ft_strlen(g_info->line) - start);
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	ft_memdel((void **)&print);
}

char					*del_char(char *buf)
{
	char	*ret;
	int		start;

	if (buf[0] == BACKSPACE && g_info->index > 0)
		move_left();
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	reprint_str_del();
	start = 0;
	ret = ft_strsub(g_info->line, start, g_info->index - start);
	start = g_info->index + 1;
	ret = ft_strjoin_free(ret, ft_strsub(g_info->line, start,
		ft_strlen(g_info->line) - start));
	ft_memdel((void **)&g_info->line);
	return (ret);
}
