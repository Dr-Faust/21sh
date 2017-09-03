/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:57:11 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/03 19:57:13 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			print_history(t_hist *hist)
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

void		add_to_history(char *line, t_hist **hist, int id)
{
	if (*hist)
		add_to_history(line, &((*hist)->next), ++id);
	else
	{
		if (!(*hist = (t_hist *)malloc(sizeof(t_hist))))
			error_exit(sh, mem_alloc_err);
		(*hist)->id = id;
		(*hist)->line = ft_strdup(line);
		(*hist)->bytes_str = ft_strdup(g_info->bytes_quote_str);
		(*hist)->next = 0;
		(*hist)->prev = 0;
		g_info->hist_counter++;
	}
}
