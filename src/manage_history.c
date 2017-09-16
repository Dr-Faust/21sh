/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:57:11 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/14 16:00:46 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		modify_ret_position(unsigned int *curr_position,
			unsigned int *ret_position)
{
	if (*curr_position > g_info->win_width)
	{
		*ret_position += *curr_position;
		*curr_position %= g_info->win_width;
		*curr_position = g_info->win_width - *curr_position;
		*ret_position += *curr_position;
	}
	else
	{
		*ret_position += *curr_position;
		*curr_position = g_info->win_width - *curr_position;
		*ret_position += *curr_position;
	}
	*curr_position = 0;
}

unsigned int	get_position(unsigned int index)
{
	unsigned int	ret_position;
	unsigned int	curr_position;

	index = 0;
	ret_position = 0;
	curr_position = g_info->prompt_len + 1;
	while (g_info->line[index])
	{
		if (g_info->line[index] == '\n')
			modify_ret_position(&curr_position, &ret_position);
		index++;
		curr_position++;
	}
	ret_position += curr_position;
	return (ret_position);
}

bool			print_history(t_hist *hist)
{
	while (hist)
	{
		ft_printf("%*d %s->%s %s\n", 4, hist->id, CYAN, DEF, hist->line);
		hist = hist->next;
	}
	return (1);
}

void		add_prev_elem(t_hist **hist)
{
	if ((*hist)->next)
	{
		(*hist)->next->prev = *hist;
		add_prev_elem(&((*hist)->next));
	}
}

void		add_to_history(char *line, t_hist **hist, unsigned int id)
{
	if (*hist)
	{
		if (((*hist)->next) == 0)
			if (!ft_strcmp(line, (*hist)->line))
				return ;
		add_to_history(line, &((*hist)->next), ++id);
	}
	else
	{
		if (!(*hist = (t_hist *)malloc(sizeof(t_hist))))
			error_exit(sh, mem_alloc_err);
		(*hist)->id = id;
		(*hist)->line = ft_strdup(line);
		(*hist)->next = 0;
		(*hist)->prev = 0;
		g_info->hist_counter++;
	}
}
