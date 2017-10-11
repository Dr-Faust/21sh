#include "minishell.h"

int		check_IO(char **args, int *i)
{
	if (!ft_strcmp(args[*i], ">"))
		return (set_single_otuput_fd(args, i));
	else if (!ft_strcmp(args[*i], ">>"))
		return (set_double_otuput_fd(args, i));
	else if (!ft_strcmp(args[*i], "<"))
		return (set_input_fd(args, i));
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

int		check_redirections(char **args, t_env *env_info, char *path)
{
	int		i;
	bool	error;

	error = false;
	if (find_redirection(args))
	{
		i = -1;
		while (args[++i])
			if (check_IO(args, &i))
			{
				error = true;
				ft_memdel((void **)&path);
				break ;
			}
		if (error == false)
			launch(args, env_info, path);
		dup2(g_info->stdin_fd_copy, STDIN_FILENO);
		dup2(g_info->stdout_fd_copy, STDOUT_FILENO);
		return (1);
	}
	return (0);
}
