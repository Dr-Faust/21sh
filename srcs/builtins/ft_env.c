/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 20:40:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/10/19 20:40:14 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_output(char **args, t_env *env_info, int i)
{
	int		fd;

	fd = open(args[i + 1], O_APPEND | O_RDWR | O_CREAT, 0664);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	while (env_info != 0)
	{
		ft_printf("%s=%s\n", env_info->name, env_info->content);
		env_info = env_info->next;
	}
	dup2(g_info->stdout_fd_copy, STDOUT_FILENO);
}

void	single_output(char **args, t_env *env_info, int i)
{
	int		fd;

	fd = open(args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0664);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	while (env_info != 0)
	{
		ft_printf("%s=%s\n", env_info->name, env_info->content);
		env_info = env_info->next;
	}
	dup2(g_info->stdout_fd_copy, STDOUT_FILENO);
}

int		ft_env(char **args, t_env *env_info)
{
	int		i;

	i = 1;
	if (args[i])
	{
		if (!(ft_strcmp(args[i], ">")) && (args[i + 1]))
			single_output(args, env_info, i);
		else if (!(ft_strcmp(args[i], ">>")) && (args[i + 1]))
			double_output(args, env_info, i);
		else if (!(ft_strcmp(args[i], ">")) && (!args[i + 1]))
			return (error_return(env, too_few_args, "single_output"));
		else if (!(ft_strcmp(args[i], ">>")) && (!args[i + 1]))
			return (error_return(env, too_few_args, "double_output"));
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
