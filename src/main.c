/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:10:03 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/10 21:19:10 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(t_env **env_info)
{
	char	*line;
	int		status;
	int		i;
	char	***args;

	status = 1;
	while (status)
	{
		i = 0;
		write_prompt();
		line = read_line();
		while (line[i])
		{
			if ((line[i] == 34 || line[i] == 39) &&
				valid_quote(line, i + 1, line[i]) != -1)
				break ;
			else if ((line[i] == 34 || line[i] == 39) &&
				valid_quote(line, i + 1, line[i]) == -1)
				parse_quotes(&line, &i, line[i]);
			else
				i++;
		}
		if (!(args = ft_memalloc(sizeof(char **) * (count_commands(line) + 1))))
			error_exit(mem_alloc_err);
		status = split_line(&(line[0]), env_info, status, args);
		ft_memdel((void **)&args);
		ft_memdel((void **)&line);
	}
}

int			main(void)
{
	extern char	**environ;
	t_env		*env_info;

	env_info = get_env_info(environ);
	minishell(&env_info);
	return (EXIT_SUCCESS);
}
