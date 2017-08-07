/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_del_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 16:19:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/07 20:51:28 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*add_char(char chr, char *buffer, t_win *w)
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
	print[0] = chr;
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

/*static void	move_up_on_count(t_win *w)
{
	while (w->str_count-- > 0)
		tputs(tgetstr("up", 0), 1, &ft_put_my_char);
	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
}*/

/*static void	reprint_str(t_win *w, char *buffer)
{
	char	*print;
	int		start;
//	int		count;

	start = w->index + 1;
	print = ft_strsub(buffer, start, ft_strlen(buffer) - start);
	tputs(tgetstr("sc", 0), 1, &ft_put_my_char);
	ft_printf("%s", print);
	if ((w->position + 2) % w->size == 0)
		ft_putchar('\n');
	tputs(tgetstr("dc", 0), 1, &ft_put_my_char);
//	tputs(tgetstr("rc", 0), 1, &ft_put_my_char);
//	if (((int)ft_strlen(buffer) + w->prompt_len - 1) % w->size == 0)
//		tputs(tgetstr("up", 0), 1, &ft_put_my_char);

//	while (buffer[w->index])
//		move_right(w);
//	tputs(tgetstr("dc", 0), 1, &ft_put_my_char);
	move_up_on_count(w);
	ft_printf("%s", print);
	move_up_on_count(w);
	ft_memdel((void **)&print);
}*/

char		*del_char(char *buf, char *buffer, t_win *w)
{
	char	*ret;
	int		start;

	if (!(ret = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	if (buf[0] == BACKSPACE && w->index > 0)
	{
		move_left(w);
	//	tputs(tgetstr("le", 0), 1, &ft_put_my_char);
	//	tputs(tgetstr("dc", 0), 1, &ft_put_my_char);
	//	tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	//	if ((w->position + 1) % w->size == 0 && buf[0] == BACKSPACE)
	//		ft_printf("here\n");
		if ((w->position + 2) % w->size == 0)
		{
		//	ft_printf("here\n");
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
			tputs(tgetstr("dc", 0), 1, &ft_put_my_char);
		//	tputs(tgetstr("le", 0), 1, &ft_put_my_char);
		}
	}
	tputs(tgetstr("dc", 0), 1, &ft_put_my_char);
/*	if (w->position % w->size == 0 && buf[0] == BACKSPACE)
	{
		tputs(tgetstr("up", 0), 1, &ft_put_my_char);
		w->position = 0;
		while (w->position++ < w->size - 1)
			tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
		tputs(tgetstr("le", 0), 1, &ft_put_my_char);
		tputs(tgetstr("dc", 0), 1, &ft_put_my_char);
		tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	}*/
//	if ((int)ft_strlen(buffer) + w->prompt_len > w->size)
//		reprint_str(w, buffer);
	start = 0;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start, w->index - start));
	start = w->index + 1;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start,
		ft_strlen(buffer) - start));
	ft_memdel((void **)&buffer);
	return (ret);
}
