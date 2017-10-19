/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 20:31:37 by opodolia          #+#    #+#             */
/*   Updated: 2017/10/19 20:31:39 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_dir(t_env *env_info)
{
	char	*home;

	home = NULL;
	while (env_info)
	{
		if (!ft_strcmp(env_info->name, "HOME"))
		{
			home = ft_strdup(env_info->content);
			break ;
		}
		env_info = env_info->next;
	}
	return (home);
}

void		add_line_to_history_file(char *line, t_env *env_info)
{
	int		fd;
	char	*home_dir;
	char	*path;

	if (!(home_dir = get_home_dir(env_info)))
		return ;
	path = ft_strjoin(home_dir, "/.21sh_history");
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, S_IWUSR | S_IRUSR);
	if (fd > 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		close(fd);
	}
	ft_memdel((void **)&home_dir);
	ft_memdel((void **)&path);
}
