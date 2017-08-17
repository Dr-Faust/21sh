/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:50:42 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/17 20:27:08 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*current_dir(void)
{
	char	*dir;
	int		len;
	int		start;
	char	path[PATH_LEN];

	dir = 0;
	getcwd(path, PATH_LEN);
	len = ft_strlen(path);
	start = len - 1;
	while (path[start] != '/')
		start--;
	dir = ft_strsub(path, start + 1, len - start);
	ft_printf("%s%s%s%s%s ", B_YELLOW, "➜  ", B_GREEN, dir, DEF);
	return (dir);
}

int			write_prompt()
{
//	char			*host_name;
//	char			*comp;
//	char			*user;
	char			*curr_dir;
	int				prompt_len;

//	ioctl(0, TIOCGWINSZ, &win_size);
	prompt_len = -1;
//	g_win_size = win_size.ws_col;
//	while (++w->prompt_len < g_win_size)
//		write(1, "_", 1);
/*	user = getpwuid(getuid())->pw_name;
	ft_printf("%s%s%s%s", B_YELLOW, user, B_BLUE, "][");
	if (!(host_name = ft_memalloc(sizeof(char *) * 256)))
		error_exit(sh, mem_alloc_err);
	gethostname(host_name, 256);
	comp = ft_strndup(host_name, '.');
	ft_printf("%s%s%s%s%s", B_GREEN, comp, B_RED, " ✗ ", B_CYAN);*/
//	ft_printf("%s%s%s", B_GREEN, "✗ ", B_BLUE);
	curr_dir = current_dir();
	prompt_len = /*ft_strlen(user) + ft_strlen(comp) + */ft_strlen(curr_dir) + 4;
	ft_memdel((void **)&curr_dir);
//	ft_memdel((void **)&host_name);
//	ft_memdel((void **)&comp);
	return (prompt_len);
}
