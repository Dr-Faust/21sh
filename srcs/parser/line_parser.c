#include "minishell.h"

void	clean_up(char **args)
{
	int		i;

	i = -1;
	if (args && *args)
		while (args[++i])
			ft_memdel((void **)&args[i]);
	ft_memdel((void **)&args);
}

int		parse_line(char *line, t_env **env_info, t_hist **hist)
{
	t_pipe	*p;
	int		status;

	if (!(p = (t_pipe *)ft_memalloc(sizeof(t_pipe))))
			error_exit(sh, mem_alloc_err);
	p->pipe_found = false;
	status = split_line(line, env_info, hist, p);
	ft_memdel((void **)&p);
	return (status);
}