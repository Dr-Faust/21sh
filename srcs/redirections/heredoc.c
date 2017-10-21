/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 19:22:02 by opodolia          #+#    #+#             */
/*   Updated: 2017/10/19 19:23:14 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_line_reader(char *marker, t_hist **hist, t_pipe *p, char **args)
{
	char	*str;
	char	*line;
	int		i;

	i = -1;
	str = read_line(hist);
	g_info->quote_line = ft_strjoin_free_first(g_info->quote_line, str);
	if (ft_strcmp(str, marker))
		line = ft_strdup(str);
	if (!ft_strcmp(str, marker))
	{
		line = ft_strnew(1);
		p->r->marker_found = true;
	}
	if (!ft_strcmp(g_info->quote_line, str))
	{
		while (args[++i])
			ft_strdel(&args[i]);
		args[0] = ft_strdup(line);
		args[0][ft_strlen(args[0]) - 1] = '\0';
		p->r->heredoc_found = false;
		p->r->marker_found = true;
	}
	ft_memdel((void **)&str);
	return (line);
}

char	*get_heredoc(char *marker, t_hist **hist, t_pipe *p, char **args)
{
	char	*line;

	p->r->marker_found = false;
	marker = ft_strjoin(marker, "\n\0");
	g_info->marker = ft_strdup(marker);
	g_info->quote_line = ft_strdup(marker);
	if (!(line = (char *)ft_memalloc(sizeof(char) * 1)))
		error_exit(sh, mem_alloc_err);
	while (!p->r->marker_found)
	{
		g_info->prompt_len = 9;
		ft_printf("%s%s%s", MAGENTA, "heredoc> ", DEF);
		line = ft_strjoin_free(line, heredoc_line_reader(marker, hist, p, args));
	}
	if (g_info->marker)
		ft_memdel((void **)&g_info->marker);
	ft_strdel(&g_info->quote_line);
	ft_memdel((void **)&marker);
	return (line);
}

int		manage_heredoc(char **args, t_hist **hist, t_pipe *p, int *index)
{
	char	*line;

	ft_memdel((void **)&args[*index]);
	(*index)++;
	if (!args[*index])
		return (error_return(sh, too_few_args, "heredoc"));
	line = get_heredoc(args[*index], hist, p, args);
	if (p->r->heredoc_found)
		p->r->heredoc_line = ft_strdup(line);
	ft_memdel((void **)&line);
	ft_memdel((void **)&args[*index]);
	return (0);
}

// char	*get_heredoc(char *marker, t_hist **hist)
// {
// 	char	*str;
// 	char	*line;
// 	bool	marker_found;

// 	marker_found = false;
// 	marker = ft_strjoin(marker, "\n\0");
// 	g_info->marker = ft_strdup(marker);
// 	if (!(line = (char *)ft_memalloc(sizeof(char) * 1)))
// 		error_exit(sh, mem_alloc_err);
// 	while (!marker_found)
// 	{
// 		g_info->prompt_len = 9;
// 		ft_printf("%s%s%s", MAGENTA, "heredoc> ", DEF);
// 		str = read_line(hist);
// 		g_info->quote_line = ft_strjoin_free_first(g_info->quote_line, str);
// 		if (ft_strcmp(str, marker))
// 			line = ft_strjoin_free_first(line, str);
// 		if (!ft_strcmp(str, marker))
// 			marker_found = true;
// 		ft_memdel((void **)&str);
// 	}
// 	if (g_info->marker)
// 		ft_memdel((void **)&g_info->marker);
// 	ft_memdel((void **)&marker);
// 	return (line);
// }

// int		manage_heredoc(char **args, t_hist **hist, t_pipe *p, int *index)
// {
// 	char	*line;

// 	ft_memdel((void **)&args[*index]);
// 	(*index)++;
// 	if (!args[*index])
// 		return (error_return(sh, too_few_args, "heredoc"));
// 	line = get_heredoc(args[*index], hist);
// 	p->r->heredoc_line = ft_strdup(line);
// 	ft_memdel((void **)&line);
// 	ft_memdel((void **)&args[*index]);
// 	return (0);
// }
