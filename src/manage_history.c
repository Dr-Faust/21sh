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

int			get_position(int line_indx, int byte_indx)
{
	int		position;
	int		counter;
	int		flag;

	line_indx = 0;
	byte_indx = 0;
	position = 0;
	counter = 0;
	flag = 0;
	while (g_info->line[line_indx])
	{
		if (g_info->line[line_indx] == '\n')
		{
		//	ft_printf("\nhere\n");
			position += g_info->win_size;
			counter = 0;
			flag = 1;
		}
		line_indx += g_info->bytes_str[byte_indx++] - '0';
		counter++;
	//	ft_printf("\ncounter = %d\n", counter);
	}
	if (flag)
		position += counter;
	else
		position += counter + g_info->prompt_len;
//	ft_printf("\nbytes_str = %s\n", g_info->bytes_str);
//	ft_printf("\nwin_size = %d\n", g_info->win_size);
//	ft_printf("\nprompt_len = %d\n", g_info->prompt_len);
//	ft_printf("\npos = %d\n", position);
	return (position);
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
		(*hist)->bytes_str = ft_strdup(g_info->bytes_quote_str);
		(*hist)->next = 0;
		(*hist)->prev = 0;
		g_info->hist_counter++;
	}
}
