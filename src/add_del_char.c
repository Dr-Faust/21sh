/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_del_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 16:19:56 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/22 18:18:02 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*add_char(char chr, char *buffer, int *position)
{
	char	*ret;
	int		start;
	char	*print;

	if (!(ret = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	if (!(print = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	start = 0;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start, (*position) - start));
	print[0] = chr;
	start = *position;
	print = ft_strjoin_free(print, ft_strsub(buffer, start,
				ft_strlen(buffer) - start));
	ft_putstr(tgetstr("sc", 0));
	ft_printf("%s", print);
	ft_putstr(tgetstr("rc", 0));
	ft_putstr(tgetstr("nd", 0));
	ret = ft_strjoin_free(ret, print);
	ft_memdel((void **)&buffer);
	return (ret);
}

char		*del_char(char *buf, char *buffer, int *position)
{
	char	*ret;
	int		start;

	if (!(ret = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	if (buf[0] == BACKSPACE && (*position) > 0)
	{
		ft_putstr(tgetstr("le", 0));
		(*position)--;
	}
	ft_putstr(tgetstr("dc", 0));
	start = 0;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start, (*position) - start));
	start = *position + 1;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start,
		ft_strlen(buffer) - start));
	ft_memdel((void **)&buffer);
	return (ret);
}
