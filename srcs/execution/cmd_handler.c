#include "minishell.h"

/*int			cmd_handler_2(char **args, t_env **env_info)
{
	int		i;
	int		j;
	char	*args_aux[256];

	i = 0;
	j = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<"))
			break;
		args_aux[i] = args[i];
		i++;
	}
	while (args[j])
	{
		if (!ft_strcmp(args[j], ">"))
		{
			if (!args[j + 1])
				return (error_return(sh, too_few_args, 0));
			return (redirect_output(*env_info, args_aux, args[j + 1]));
		}
		j++;
	}
	return (treat_path(args, *env_info));
}*/


int			cmd_handler(char **args, t_env **env_info, t_hist *hist)
{
	if (!args[0])
		return (1);
//	if (!ft_strcmp(args[0], "echo"))
//		return (ft_echo(args));
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, env_info));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(args,*env_info));
	else if (!ft_strcmp(args[0], "setenv"))
		return (ft_setenv(env_info, args[1], args[2], args));
	else if (!ft_strcmp(args[0], "unsetenv"))
		return (ft_unsetenv(*env_info, args[1]));
	else if (!ft_strcmp(args[0], "help"))
		return (ft_help());
	else if (!ft_strcmp(args[0], "history"))
		return (print_history(hist));
	else if (!ft_strcmp(args[0], "exit"))
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_info->default_term);
		tgetent(0, getenv("TERM"));
		return (0);
	}
	else if (!ft_strcmp(args[0], "cat"))
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_info->default_term);
	return (treat_path(args, *env_info));
//	return (cmd_handler_2(args, env_info));
}
