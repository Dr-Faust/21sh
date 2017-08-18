/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:10:03 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/18 20:47:08 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(t_env **env_info)
{
	char	*line;
	int		status;
	char	***args;
	t_win	w;

	status = 1;
	while (status)
	{
		g_line = 0;
	//	singleton_prompt(1);
	//	manage_signal();
		w.prompt_len = write_prompt();
		line = read_line(&w);
		line = parser(line, &w);
		ft_printf("line = %s\n", line);
	//	singleton_prompt(2);
		if (!(args = ft_memalloc(sizeof(char **) * (count_commands(line) + 1))))
			error_exit(sh, mem_alloc_err);
		status = split_line(&(line[0]), env_info, status, args);
		ft_memdel((void **)&args);
		ft_memdel((void **)&line);
		ft_memdel((void **)&w.bytes_str);
	}
}

int			main(void)
{
	extern char	**environ;
	t_env		*env_info;

	set_terminal();
//	ft_putstr("\x1B[?7h");
	env_info = get_env_info(environ);
	minishell(&env_info);
	return (EXIT_SUCCESS);
}
