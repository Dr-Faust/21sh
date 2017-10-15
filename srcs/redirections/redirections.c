#include "minishell.h"

int		check_IO(char **args, t_hist **hist, int index, t_pipe *p)
{
	if (!ft_strcmp(args[index], ">"))
	{
		p->r->index = index;
		p->r->single_output_found = true;
	}
	else if (!ft_strcmp(args[index], ">>"))
	{
		p->r->index = index;
		p->r->double_output_found = true;
	}
	else if (!ft_strcmp(args[index], "<"))
	{
		p->r->index = index;
		p->r->input_found = true;
	}
	else if (!ft_strcmp(args[index], "<<"))
	{
		p->r->index = index;
		p->r->heredoc_found = true;
		return (manage_heredoc(args, hist, p));
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
		index = -1;
		while (args[++(index)])
			if (check_IO(args, hist, index, p))
				return (1);
	}
	return (0);
}
