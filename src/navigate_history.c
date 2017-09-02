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

static void	get_new_line(t_hist *hist)
{
	int		i;

	i = 0;
	while (g_info->line_index > 0)
		move_left();
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	ft_memdel((void **)&g_info->line);
	ft_memdel((void **)&g_info->bytes_str);
	g_info->line = ft_strdup(hist->line);
	g_info->bytes_str = ft_strdup(hist->bytes_str);
	g_info->bytes_index = ft_strlen(g_info->bytes_str);
	g_info->position = g_info->prompt_len + g_info->bytes_index;
	while (i < g_info->bytes_index)
		g_info->line_index += g_info->bytes_str[i++] - '0';
	ft_printf("%s", g_info->line);
}

static void	get_start_line(void)
{
	int		i;

	i = 0;
	g_info->line = ft_strdup(g_info->hist_start_line);
	g_info->bytes_str = ft_strdup(g_info->hist_start_line_bytes);
	g_info->bytes_index = ft_strlen(g_info->bytes_str);
	g_info->position = g_info->prompt_len + g_info->bytes_index;
	while (i < g_info->bytes_index)
		g_info->line_index += g_info->bytes_str[i++] - '0';
	g_info->hist_search_flag = 1;
	ft_printf("%s", g_info->line);
}

static void	clear_line(int	*hist_counter)
{
	while (g_info->line_index > 0)
		move_left();
	tputs(tgetstr("cd", 0), 1, &ft_put_my_char);
	ft_memdel((void **)&g_info->line);
	ft_memdel((void **)&g_info->bytes_str);
	if (!g_info->hist_search_flag)
		get_start_line();
	else
	{
		g_info->line = ft_strnew(1);
		g_info->bytes_str = ft_strnew(1);
		g_info->bytes_index = 0;
		g_info->position = g_info->prompt_len;
		g_info->line_index = 0;
	}
	*hist_counter += 1;
}

void		print_prev_hist(t_hist *hist, int *hist_counter)
{
	if (g_info->hist_search_flag)
	{
		if (g_info->hist_start_line)
		{
			ft_memdel((void **)&g_info->hist_start_line);
			ft_memdel((void **)&g_info->hist_start_line_bytes);
		}
		g_info->hist_start_line = ft_strdup(g_info->line);
		g_info->hist_start_line_bytes = ft_strdup(g_info->bytes_str);
		g_info->hist_search_flag = 0;
	}
	if (*hist_counter > 1)
		*hist_counter -= 1;
	while (hist->id != *hist_counter)
		hist = hist->next;
	if (!ft_strncmp(g_info->hist_start_line, hist->line,
			ft_strlen(g_info->hist_start_line)) && hist)
		get_new_line(hist);
	else if (hist->id > 1)
		print_prev_hist(hist->prev, hist_counter);
}

void		print_next_hist(t_hist *hist, int *hist_counter)
{
	if (g_info->hist_search_flag)
	{
		if (g_info->hist_start_line)
		{
			ft_memdel((void **)&g_info->hist_start_line);
			ft_memdel((void **)&g_info->hist_start_line_bytes);
		}
		g_info->hist_start_line = ft_strdup(g_info->line);
		g_info->hist_start_line_bytes = ft_strdup(g_info->bytes_str);
		g_info->hist_search_flag = 0;
	}
	if (*hist_counter == g_info->hist_counter)
		return (clear_line(hist_counter));
	if (*hist_counter < g_info->hist_counter)
		*hist_counter += 1;
	while (hist->id != *hist_counter)
		hist = hist->next;
	if (!ft_strncmp(g_info->hist_start_line, hist->line,
		ft_strlen(g_info->hist_start_line)) && hist)
		get_new_line(hist);
	else if (hist->id > 1)
		print_next_hist(hist->next, hist_counter);
}
