/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 20:52:58 by opodolia          #+#    #+#             */
/*   Updated: 2017/10/19 20:53:06 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_flags(t_pipe *p)
{
	p->r->write_found = false;
	p->r->append_found = false;
	p->r->read_found = false;
	p->r->heredoc_found = false;
	p->r->output_fd_found = false;
	p->r->input_fd_found = false;
	p->r->close_fd_found = false;
	p->r->input_file_found = false;
}

void	clean_up(char **args)
{
	int		i;

	i = -1;
	if (args && *args)
		while (args[++i])
			ft_memdel((void **)&args[i]);
	ft_memdel((void **)&args);
}

int		parse_line(char *line, t_env **env_info, t_hist **hist)
{
	t_pipe	*p;
	int		status;

	if (!(p = (t_pipe *)ft_memalloc(sizeof(t_pipe))))
		error_exit(sh, mem_alloc_err);
	if (!(p->r = (t_redirect *)ft_memalloc(sizeof(t_redirect))))
		error_exit(sh, mem_alloc_err);
	status = split_line(line, env_info, hist, p);
	ft_memdel((void **)&p->r);
	ft_memdel((void **)&p);
	return (status);
}
