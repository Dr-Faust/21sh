/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_del_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 16:19:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/10 21:11:31 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*add_char(char *buf, char *buffer, t_win *w)
{
	char	*ret;
	int		start;
	char	*print;

	if (!(ret = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	if (!(print = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	start = 0;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start, w->index - start));
	print = ft_strjoin_free_first(print, buf);
	start = w->index;
	print = ft_strjoin_free(print, ft_strsub(buffer, start,
		ft_strlen(buffer) - start));
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
	tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	ret = ft_strjoin_free(ret, print);
	if (((int)ft_strlen(ret) + w->prompt_len - 1) % w->size == 0)
		tputs(tgetstr("up", 0), 1, &ft_put_my_char);
	if ((w->position + 1) % w->size == 0)
		ft_putchar('\n');
	ft_memdel((void **)&buffer);
	return (ret);
}

static void	reprint_str(t_win *w, char *buffer)
{
	char	*print;
	int		start;

	start = w->index + 1;
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

	if (!(ret = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	if (buf[0] == BACKSPACE && w->index > 0)
		move_left(w);
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	reprint_str(w, buffer);
	start = 0;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start, w->index - start));
	start = w->index + 1;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start,
		ft_strlen(buffer) - start));
	ft_memdel((void **)&buffer);
	return (ret);
}
