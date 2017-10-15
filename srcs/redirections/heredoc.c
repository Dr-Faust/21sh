#include "minishell.h"

char	*get_heredoc(char *marker, t_hist **hist)
{
	char	*str;
	char	*line;
	bool	marker_found;

	marker_found = false;
	marker = ft_strjoin_free_first(marker, "\n\0");
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
			marker_found = 1;
		if (!str[0] && !g_info->quote_line[0])
			marker_found = true;
		ft_memdel((void **)&str);
	}
	ft_memdel((void **)&marker);
	return (line);
}



int		manage_heredoc(char **args, int *i, t_hist **hist, t_pipe *p)
{
	ft_memdel((void **)&args[*i]);
	(*i)++;
	if (!args[*i])
		return (error_return(sh, too_few_args, "heredoc"));
	p->heredoc_line = get_heredoc(args[*i], hist);
	p->heredoc_found = true;
	return (0);
}