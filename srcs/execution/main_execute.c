/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 14:55:14 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/28 19:15:52 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main_execute(t_pipe *p, t_env **env_info, t_hist **hist)
{
	char	*path;
	char	**args;

	args = split_command(p->pipe_cmds[p->index]);
	if (!builtins_handler(args, env_info, *hist))
	{
		if (!ft_strcmp(args[0], "exit"))
		{
			tcsetattr(STDIN_FILENO, TCSADRAIN, &g_info->default_term);
			clean_up(args);
			return (0);
		}
		if ((path = treat_path(args, *env_info)))
		{
			if (check_redirections(args, hist, p))
				return (1);
			tcsetattr(STDIN_FILENO, TCSADRAIN, &g_info->default_term);
			launch(args, *env_info, p, path);
		}
		if (!ft_strcmp(args[0], "cat") && !args[1] && p->pipe_found == false)
			ft_putchar('\n');
	}
	clean_up(args);
	return (1);
}
