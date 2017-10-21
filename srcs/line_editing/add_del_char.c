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
	if ((g_info->position + indx - 1) % g_info->win_width == 0)
		tputs(tgetstr("up", 0), 1, &ft_put_my_char);
	if ((g_info->position) % g_info->win_width == 0)
		ft_putchar('\n');
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
