/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_del_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 19:26:48 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/14 20:55:54 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reprint_str_add(t_win *w, char *buffer, char *buf)
{
	char	*print;
	int		start;

	start = w->index;
	print = ft_strdup(buf);
	print = ft_strjoin_free(print, ft_strsub(buffer, start,
		ft_strlen(buffer) - start));
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	return (print);
}

char		*add_char(char *buf, char *buffer, t_win *w)
{
	char	*ret;
	int		start;
	char	*tmp;

	start = 0;
	ret = ft_strsub(buffer, start, w->index - start);
	ret = ft_strjoin_free(ret, reprint_str_add(w, buffer, buf));
	if (((int)ft_strlen(w->bytes_str) + w->prompt_len - 1) % w->size == 0)
		tputs(tgetstr("up", 0), 1, &ft_put_my_char);
	if ((w->position + 1) % w->size == 0)
		ft_putchar('\n');
	start = 0;
//	ft_printf("str_1 = %s\n", w->bytes_str);
//	ft_printf("\ni = %d\n", w->i);
	tmp = ft_strsub(w->bytes_str, start, w->i - start);
//	ft_printf("tmp = %s\n", tmp);

	tmp = ft_strjoin_free_first(tmp, ft_itoa(w->bytes));
//	ft_printf("\ni = %d\n", w->i);
	start = w->i;
//	ft_printf("\nb_1 = %s\n", w->bytes_str);
//	ft_memdel((void **)&(w->bytes_str));
	tmp = ft_strjoin_free(tmp, ft_strsub(w->bytes_str, start,
		ft_strlen(w->bytes_str) - start));
//	ft_printf("\nb_2 = %s\n", w->bytes_str);
	ft_memdel((void **)&(w->bytes_str));
	w->bytes_str = ft_strdup(tmp);
//	ft_printf("str_2 = %s\n", w->bytes_str);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&buffer);
	return (ret);
}

static void	reprint_str_del(t_win *w, char *buffer)
{
	char	*print;
	int		start;

	start = w->index + (w->bytes_str[w->i] - '0');
	print = ft_strsub(buffer, start, ft_strlen(buffer) - start);
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	ft_memdel((void **)&print);
}

char		*del_char(char *buf, char *buffer, t_win *w)
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
	reprint_str_del(w, buffer);
	start = 0;
	ret = ft_strsub(buffer, start, w->index - start);
	start = w->index + (w->bytes_str[w->i] - '0');
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start,
		ft_strlen(buffer) - start));
	ft_memdel((void **)&(w->bytes_str));
	w->bytes_str = ft_strdup(tmp);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&buffer);
	return (ret);
}
