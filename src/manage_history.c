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

int			get_position(int index)
{
	int		ret_position;
	int		curr_position;

	index = 0;
	ret_position = 0;
	curr_position = g_info->prompt_len + 1;
	while (g_info->line[index])
	{
		if (g_info->line[index] == '\n')
		{
			if (curr_position > g_info->win_size)
			{
				//	ft_printf("\ncurr_pos_1 = %d\n", curr_position);
				ret_position += curr_position;
				curr_position %= g_info->win_size;
				curr_position = g_info->win_size - curr_position;
				ret_position += curr_position;
				//	ft_printf("\nret)_pos = %d\n", ret_position);
			}
			else
			{
				ret_position += curr_position;
				curr_position = g_info->win_size - curr_position;
				ret_position += curr_position;
				//	ft_printf("\ncounter_2 = %d\n", counter);
				//	ft_printf("\nposit_2 = %d\n", position);
			}
			curr_position = 0;
		}
		index++;
		curr_position++;
	}
	ret_position += curr_position;
	return (ret_position);
}

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
		(*hist)->next = 0;
		(*hist)->prev = 0;
		g_info->hist_counter++;
	}
}
