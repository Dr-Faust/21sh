#include "minishell.h"

char	*get_heredoc(char *marker, t_hist **hist)
{
	char	*str;
	char	*line;
	bool	marker_found;
	// char	*mark;

	marker_found = false;
	marker = ft_strjoin(marker, "\n\0");
	// mark = ft_strdup(marker);
	// if (mark)
	// 	mark = NULL;
	if (!(line = (char *)ft_memalloc(sizeof(char) * 1)))
			error_exit(sh, mem_alloc_err);
	while (!marker_found)
	{
		g_info->prompt_len = 9;
		ft_printf("%s%s%s", MAGENTA, "heredoc> ", DEF);
		str = read_line(hist);
		g_info->quote_line = ft_strjoin_free_first(g_info->quote_line, str);
		if (ft_strcmp(str, marker))
			line = ft_strjoin_free_first(line, str);
		if (!ft_strcmp(str, marker))
			marker_found = true;
		if (!str[0] && !g_info->quote_line[0])
			marker_found = true;
		ft_memdel((void **)&str);
	}
	ft_memdel((void **)&marker);
	return (line);
}

int		manage_heredoc(char **args, t_hist **hist, t_pipe *p, int index)
{
	char	*line;

	ft_memdel((void **)&args[index]);
	index++;
	if (!args[index])
		return (error_return(sh, too_few_args, "heredoc"));
	line = get_heredoc(args[index], hist);
	p->r->heredoc_line = ft_strdup(line);
	ft_memdel((void **)&line);
	ft_memdel((void **)&args[index]);
	return (0);
}