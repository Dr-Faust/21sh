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

static int	get_curr_row_position(void)
{
	char			buf[8];
	const char		cmd[] = "\033[6n";
	char			*tmp;
	int				position;
	int				i;

	position = 0;
	if (isatty(fileno(stdin)))
	{
		write(1, cmd, sizeof(cmd));
		read (0, buf, sizeof(buf));
		i = 0;
		while (buf[i] != ';')
			i++;
		i -= 2;
		tmp = ft_strsub(buf, 2, i);
		position = ft_atoi(tmp);
		/* It doesn't work!!?
		sscanf(buf,"%d",curline);
		printf("\n\rCurrent Line: %d\n\r" , curline);
		*/
	//	printf("\n\rCurrent Line: %c%c\n\r" , buf[2] ,buf[3] );
	//	ft_printf("\npos = %d\n", position);
	}
	return (position);
/*	int		y;
	WINDOW	*win;
	win = initscr();
	y = getcury(win);
	ft_printf("\ny = %d\n", y);
	endwin();
	refresh();*/
/*	char	*buf;
	char	*tmp;
	int		position;
	int		i;

	i = 0;
	position = 0;
	buf = ft_strnew(7);
	ft_putstr("\x1B[6n");
	read(STDIN_FILENO, buf, 7);
	while (buf[i] != ';')
		i++;
//	ft_printf("\ni = %d\n", i);
	i -= 2;
	tmp = ft_strsub(buf, 2, i);
///	ft_printf("\ntmp = %s\n", tmp);
//	tmp = ft_strchr(buf, '[');
//	write(1, &"4\n", 2);
	position = ft_atoi(tmp);
//	ft_printf("\npos = %d\n", position);
//	write(1, &"5\n", 2);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&buf);
	return (position);
//	return (y);*/
}

static char	*reprint_str_add(char *buf)
{
	char	*print;
	int		start;

	start = g_info->line_index;
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

char		*add_char(char *buf)
{
	char	*ret;
	int		indx;
	int		curr_row_pos;
	int		rows_in_line;

	indx = g_info->line_index;
	ret = ft_strsub(g_info->line, 0, g_info->line_index);
	ret = ft_strjoin_free(ret, reprint_str_add(buf));
	while (g_info->line[indx])
	{
		if (g_info->line[indx] == '\n')
			break ;
		indx++;
	}
	indx -= g_info->line_index;
	curr_row_pos = get_curr_row_position();
	rows_in_line = get_position(indx) / g_info->win_width;
	if (curr_row_pos > (g_info->win_height - rows_in_line) &&
		curr_row_pos <= g_info->win_height)
		if ((g_info->position + indx - 1) % g_info->win_width == 0)
			tputs(tgetstr("up", 0), 1, &ft_put_my_char);
	if ((g_info->position) % g_info->win_width == 0)
		ft_putchar('\n');
	ft_memdel((void **)&g_info->line);
	return (ret);
}

static void	reprint_str_del(void)
{
	char	*print;
	int		start;

	start = g_info->line_index + 1;
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

	if (buf[0] == BACKSPACE && g_info->line_index > 0)
		move_left();
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	reprint_str_del();
	start = 0;
	ret = ft_strsub(g_info->line, start, g_info->line_index - start);
	start = g_info->line_index + 1;
	ret = ft_strjoin_free(ret, ft_strsub(g_info->line, start,
		ft_strlen(g_info->line) - start));
	ft_memdel((void **)&g_info->line);
	return (ret);
}
