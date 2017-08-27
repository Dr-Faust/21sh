/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:10:03 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 20:39:27 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob_info	*g_info;

static void	minishell(t_env **env_info)
{
	char	*line;
	int		status;
	char	***args;

	status = 1;
	while (status)
	{
		set_terminal();
		g_info->prompt_len = write_prompt();
		line = read_line();
		line = parse_quotes(line);
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

	if (!(g_info = (t_glob_info *)ft_memalloc(sizeof(t_glob_info))))
		error_exit(sh, mem_alloc_err);
	tcgetattr(STDIN_FILENO, &g_info->default_term);
//	ft_putstr("\x1B[?7h");
	env_info = get_env_info(environ);
	minishell(&env_info);
	clean_env_info(&env_info);
	return (EXIT_SUCCESS);
}
