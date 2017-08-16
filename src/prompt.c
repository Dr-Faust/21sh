/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:50:42 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/16 20:17:51 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*current_dir(t_env *env_info)
{
	char	*dir;
	int		len;
	int		start;

	dir = 0;
	while (env_info)
	{
		if (ft_strcmp(env_info->name, "PWD"))
			env_info = env_info->next;
		else
			break ;
	}
	len = ft_strlen(env_info->content);
	start = len - 1;
	while (env_info->content[start] != '/')
		start--;
	dir = ft_strsub(env_info->content, start + 1, len - start);
	ft_printf("%s%s%s%s", dir, B_YELLOW, " ➜ ", DEF);
	return (dir);
}

void		write_prompt(t_env *env_info, t_win *w)
{
	char			*buf;
	char			*comp;
	char			*user;
	char			*curr_dir;

	ioctl(0, TIOCGWINSZ, &win_size);
	w->prompt_len = -1;
	g_win_size = win_size.ws_col;
//	while (++w->prompt_len < g_win_size)
//		write(1, "_", 1);
	user = getpwuid(getuid())->pw_name;
	ft_printf("%s%s%s%s", B_YELLOW, user, B_BLUE, "][");
	if (!(buf = ft_memalloc(sizeof(char *) * 256)))
		error_exit(sh, mem_alloc_err);
	gethostname(buf, 256);
	comp = ft_strndup(buf, '.');
	ft_printf("%s%s%s%s%s", B_GREEN, comp, B_RED, " ✗ ", B_CYAN);
	curr_dir = current_dir(env_info);
	w->prompt_len = ft_strlen(user) + ft_strlen(comp) + ft_strlen(curr_dir) + 8;
	ft_memdel((void **)&curr_dir);
	ft_memdel((void **)&buf);
	ft_memdel((void **)&comp);
}
