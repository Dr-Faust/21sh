/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 19:22:09 by opodolia          #+#    #+#             */
/*   Updated: 2017/10/19 19:24:25 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_aggregator(t_pipe *p, char **args)
{
	char	*aggr;

	aggr = args[p->r->aggr_arg_index];
	if (p->r->output_fd_found && p->r->input_file_found
		&& !p->r->input_fd_found && !p->r->close_fd_found)
		set_write_fd(args, p->r->aggr_arg_index, aggr[p->r->aggr_index - 1]
			- '0');
	else if (p->r->output_fd_found && p->r->input_fd_found)
		dup2(aggr[p->r->aggr_index + 2] - '0', aggr[p->r->aggr_index - 1]
			- '0');
	else if (p->r->output_fd_found && p->r->close_fd_found)
		close(aggr[p->r->aggr_index - 1] - '0');
	ft_memdel((void **)&args[p->r->aggr_arg_index]);
}

void	check_fd_aggregators(char **args, int *index, t_pipe *p)
{
	int		i;
	char	*aggr;

	if ((i = ft_strchr_index(args[*index], '>')) != -1)
	{
		aggr = args[*index];
		p->r->aggr_index = i;
		if (aggr[i - 1] && (aggr[i - 1] >= '0' && aggr[i - 1] <= '2'))
		{
			p->r->output_fd_found = true;
			p->r->aggr_arg_index = *index;
			if (aggr[i + 1] && aggr[i + 1] == '&' && aggr[i + 2]
				&& !aggr[i + 3] && !args[*index + 1])
			{
				if (aggr[i + 2] >= '0' && aggr[i + 2] <= '2')
					p->r->input_fd_found = true;
				else if (aggr[i + 2] == '-')
					p->r->close_fd_found = true;
			}
			else if (args[*index + 1] && !aggr[i + 1])
				p->r->input_file_found = true;
		}
	}
}

int		check_io(char **args, t_hist **hist, int *index, t_pipe *p)
{
	if (!ft_strcmp(args[*index], ">"))
	{
		p->r->write_index = *index;
		p->r->write_found = true;
	}
	else if (!ft_strcmp(args[*index], ">>"))
	{
		p->r->append_index = *index;
		p->r->append_found = true;
	}
	else if (!ft_strcmp(args[*index], "<"))
	{
		p->r->read_index = *index;
		p->r->read_found = true;
	}
	else if (!ft_strcmp(args[*index], "<<"))
	{
		p->r->heredoc_found = true;
		return (manage_heredoc(args, hist, p, index));
	}
	check_fd_aggregators(args, index, p);
	return (0);
}

bool	find_redirection(char **args)
{
	int		i;
	int		j;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<")
			|| !ft_strcmp(args[i], ">>") || !ft_strcmp(args[i], "<<"))
			return (true);
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '>')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

int		check_redirections(char **args, t_hist **hist, t_pipe *p)
{
	int		index;

	if (find_redirection(args))
	{
		index = 0;
		while (args[index])
		{
			if (check_io(args, hist, &index, p))
				return (1);
			index++;
		}
	}
	return (0);
}
