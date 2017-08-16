/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:10:03 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/16 20:30:47 by opodolia         ###   ########.fr       */
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
		g_sig_flag = 0;
	//	singleton_prompt(1);
		g_sig_flag = manage_signal();
	//	ft_printf("flag_1 = %d\n", g_sig_flag);
		if (!g_sig_flag)
			write_prompt(*env_info, &w);
		else
			line = ft_strdup("\n\0");
	//	singleton_prompt(2);
		line = read_line(&w);
		line = parser(line, &w);
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
	ft_putstr("\x1B[?7h");
	env_info = get_env_info(environ);
	minishell(&env_info);
	return (EXIT_SUCCESS);
}
