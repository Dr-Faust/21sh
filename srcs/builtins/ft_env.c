#include "minishell.h"

static void	redirrect(char **args, t_env *env_info, int i)
{
	int		fd;
	int		std_out;
	
	fd = open(args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0600); 
	std_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO); 
	close(fd);
	while (env_info != 0)
	{
		ft_printf("%s=%s\n", env_info->name, env_info->content);
		env_info = env_info->next;
	}
	dup2(std_out, STDOUT_FILENO);
}

int			ft_env(char **args, t_env *env_info)
{
	int		i;
	
	i = 1;
	if (args[i])
	{
		if (!(ft_strcmp(args[i], ">")) && (args[i + 1]))
			redirrect(args, env_info, i);
		else if (!(ft_strcmp(args[i], ">")) && (!args[i + 1]))
			return (error_return(env, too_few_args, 0));
		else
			return (error_return(env, incorrect_param, args[1]));
	}
	else
		while (env_info != 0)
		{
			ft_printf("%s=%s\n", env_info->name, env_info->content);
			env_info = env_info->next;
		}
	return (1);
}
