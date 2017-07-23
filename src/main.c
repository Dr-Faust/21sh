/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:10:03 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/23 19:09:24 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(t_env **env_info)
{
	char	*line;
	int		status;
	char	***args;
	int		prompt_len;

	status = 1;
	while (status)
	{
		prompt_len = write_prompt(*env_info);
		line = read_line(prompt_len);
		line = parser(line, prompt_len);
		if (!(args = ft_memalloc(sizeof(char **) * (count_commands(line) + 1))))
			error_exit(sh, mem_alloc_err);
		status = split_line(&(line[0]), env_info, status, args);
		ft_memdel((void **)&args);
		ft_memdel((void **)&line);
	}
}

int			main(void)
{
	extern char	**environ;
	t_env		*env_info;

	set_terminal();
	env_info = get_env_info(environ);
	minishell(&env_info);
	return (EXIT_SUCCESS);
}
