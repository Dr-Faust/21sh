/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:50:42 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/05 15:40:24 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_prompt(void)
{
	struct winsize	win;
	int				i;
	char			*buf;
	char			*tmp;
	char			*comp;

	ioctl(0, TIOCGWINSZ, &win);
	i = -1;
	while (++i < win.ws_col)
		write(1, "_", 1);
	comp = getpwuid(getuid())->pw_name;
	ft_printf("%s%s%s%s", B_YELLOW, comp, B_BLUE, "][");
	buf = ft_memalloc(sizeof(char *) * 256);
	gethostname(buf, 256);
	tmp = ft_strndup(buf, '.');
	ft_printf("%s%s%s%s%s", B_GREEN, tmp, B_CYAN, ":>> ", DEF);
	ft_memdel((void **)&buf);
	ft_memdel((void **)&tmp);
}
