#include "minishell.h"

int		builtins_handler(char **args, t_env **env_info, t_hist *hist)
{
	if (!args[0])
		return (1);
	// else if (!ft_strcmp(args[0], "echo"))
	// 	return (ft_echo(args));
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, env_info));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(args, *env_info));
	else if (!ft_strcmp(args[0], "setenv"))
		return (ft_setenv(env_info, args[1], args[2], args));
	else if (!ft_strcmp(args[0], "unsetenv"))
		return (ft_unsetenv(*env_info, args[1]));
	else if (!ft_strcmp(args[0], "help"))
		return (ft_help());
	else if (!ft_strcmp(args[0], "history"))
		return (print_history(hist));
	return (0);
}