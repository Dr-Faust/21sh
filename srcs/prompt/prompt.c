/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:50:42 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 20:31:30 by opodolia         ###   ########.fr       */
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

int			write_prompt(void)
{
	char			*curr_dir;
	int				prompt_len;

	prompt_len = -1;
	curr_dir = current_dir();
	prompt_len = ft_strlen(curr_dir) + 4;
	ft_memdel((void **)&curr_dir);
	return (prompt_len);
}
