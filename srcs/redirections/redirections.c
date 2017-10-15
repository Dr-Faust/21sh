#include "minishell.h"

int		check_IO(char **args, int *i, t_hist **hist, t_pipe *p)
{
	if (!ft_strcmp(args[*i], ">"))
		return (set_single_otuput_fd(args, i));
	else if (!ft_strcmp(args[*i], ">>"))
		return (set_double_otuput_fd(args, i));
	else if (!ft_strcmp(args[*i], "<"))
		return (set_input_fd(args, i));
	else if (!ft_strcmp(args[*i], "<<"))
		return (manage_heredoc(args, i, hist, p));
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
	int		i;

	if (find_redirection(args))
	{
		i = -1;
		while (args[++i])
			if (check_IO(args, &i, hist, p))
				return (1);
	}
	return (0);
}
