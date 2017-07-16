/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:50:42 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/16 18:35:01 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	current_dir(t_env *env_info)
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
	ft_memdel((void **)&dir);
}

void		write_prompt(t_env *env_info)
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
	ft_printf("%s%s%s%s%s", B_GREEN, tmp, B_RED, " ✗ ", B_CYAN);
	current_dir(env_info);
	ft_memdel((void **)&buf);
	ft_memdel((void **)&tmp);
}
