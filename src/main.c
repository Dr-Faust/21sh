/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:10:03 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/30 17:18:50 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob_info	*g_info;

static void	clean_history(t_hist **hist)
{
	if (!(*hist))
		return ;
	if ((*hist)->next != 0)
		clean_history(&(*hist)->next);
	ft_memdel((void **)&(*hist)->line);
	ft_memdel((void **)&(*hist)->bytes_str);
	ft_memdel((void **)&(*hist));
}

static void	clean_info(char **line, char ***args)
{
	ft_memdel((void **)&args);
	ft_memdel((void **)&(*line));
	ft_memdel((void **)&g_info->bytes_quote_str);
	ft_memdel((void **)&g_info->hist_start_line);
	ft_memdel((void **)&g_info->hist_start_line_bytes);
}

static void	minishell(t_env **env_info)
{
	char	*line;
	int		status;
	char	***args;
	t_hist	*hist;

	status = 1;
	hist = 0;
	g_info->hist_counter = 0;
	while (status)
	{
		set_terminal();
		g_info->prompt_len = write_prompt();
		line = read_line(&hist);
		line = parse_quotes(line, &hist);
		//ft_printf("\nline = %s\n", line);
		if (!(args = ft_memalloc(sizeof(char **) * (count_commands(line) + 1))))
			error_exit(sh, mem_alloc_err);
		status = split_line(&(line[0]), env_info, hist, args);
		if (line[0])
		{
			add_to_history(line, &hist, 1);
			add_prev_elem(&hist);
		}
		clean_info(&line, args);
	}
	clean_history(&hist);
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
