/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 16:19:21 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/30 17:15:46 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_prev_hist(t_hist *hist, int *hist_counter)
{
	t_hist	*prev;

	while (g_info->line_index > 0)
		move_left();
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	prev = hist;
	while (prev->id != *hist_counter)
		prev = prev->next;
	*hist_counter = *hist_counter - 1;
	ft_memdel((void **)&g_info->line);
	ft_memdel((void **)&g_info->bytes_str);
	g_info->line = ft_strdup(prev->line);
	g_info->bytes_str = ft_strdup(prev->bytes_str);
	g_info->bytes_index = ft_strlen(g_info->bytes_str);
	g_info->position = g_info->prompt_len + g_info->bytes_index;
	g_info->line_index = g_info->bytes_index;
	ft_printf("%s", g_info->line);
}

static void	create_history(char *line, t_hist **hist, int id)
{
	if (!(*hist = (t_hist *)malloc(sizeof(t_hist))))
		error_exit(sh, mem_alloc_err);
	(*hist)->id = id;
	(*hist)->line = ft_strdup(line);
	(*hist)->bytes_str = ft_strdup(g_info->bytes_quote_str);
	(*hist)->next = 0;
	g_info->hist_counter++;
}

void		add_to_history(char *line, t_hist **hist, int id)
{	
	if (*hist)
		add_to_history(line, &((*hist)->next), ++id);
	else
		create_history(line, hist, id);
}
