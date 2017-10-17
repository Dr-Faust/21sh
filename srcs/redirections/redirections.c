#include "minishell.h"

int		check_IO(char **args, t_hist **hist, int index, t_pipe *p)
{
	if (!ft_strcmp(args[index], ">"))
	{
		p->r->write_index = index;
		p->r->write_found = true;
	}
	else if (!ft_strcmp(args[index], ">>"))
	{
		p->r->append_index = index;
		p->r->append_found = true;
	}
	else if (!ft_strcmp(args[index], "<"))
	{
		p->r->read_index = index;
		p->r->read_found = true;
	}
	else if (!ft_strcmp(args[index], "<<"))
	{
		p->r->heredoc_found = true;
		return (manage_heredoc(args, hist, p, index));
	}
	return (0);
}

bool	find_redirection(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<")
			|| !ft_strcmp(args[i], ">>") || !ft_strcmp(args[i], "<<"))
			return (true);
		i++;
	}
	return (false);
}

int		check_redirections(char **args, t_hist **hist, t_pipe *p)
{
	int 	index;

	if (find_redirection(args))
	{
		index = 0;
		while (args[index])
		{
			if (check_IO(args, hist, index, p))
				return (1);
			index++;
		}
	}
	return (0);
}
