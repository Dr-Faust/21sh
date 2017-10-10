#include "minishell.h"

/*int		redirect_input(t_env *env_info, char *args[], char *input_file,
		char *output_file)
{
	int		fd;
	pid_t	pid;

	if ((pid = fork()) == -1)
		return (error_return(sh, chld_proc_not_crtd, NULL));
	if (pid == 0)
	{
		fd = open(input_file, O_RDONLY, 0600);  
		dup2(fd, STDIN_FILENO);
		close(fd);
		fd = open(output_file, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		dup2(fd, STDOUT_FILENO);
		close(fd);		 
		if (execve(args[0], args, env_info) == -1)
		{
			error_return(sh, err_cal_fork, NULL);
			kill(getpid(), SIGTERM);
		}
	}
	waitpid(pid, NULL, 0);
	return (1);
}*/

int		 clean_info(t_redirect *info, char *path)
{
	int		i;

	i = -1;
	while (info->args[++i])
		ft_memdel((void **)&info->args[i]);
	ft_memdel((void **)&info->args);
	ft_memdel((void **)&info->input_file);
	ft_memdel((void **)&info->output_file);
	ft_memdel((void **)&info);
	ft_memdel((void **)&path);
	return (1);
}

int		redirect_output(t_env *env_info, t_redirect *info, char *path)
{
	int		fd;
	pid_t	pid;
	char	**env;
	int		i;

	i = -1;
	env = env_to_arr(env_info);
	if ((pid = fork()) == -1)
		return (error_return(sh, chld_proc_not_crtd, NULL));
	if (pid == 0)
	{
		fd = open(info->output_file, O_CREAT | O_TRUNC | O_WRONLY, 0600); 
		dup2(fd, STDOUT_FILENO); 
		close(fd);
		if (execve(path, info->args, env) == -1)
		{
			error_return(sh, err_cal_fork, NULL);
			kill(getpid(), SIGTERM);
		}		 
	}
	while (env[++i])
		ft_memdel((void **)&env[i]);
	ft_memdel((void **)&env);
	//clean_info(info, env, path);
	waitpid(pid, NULL, 0);
	return (1);
}

bool	check_params(t_env *env_info, char *args[], t_redirect *info,
		char *path)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">"))
		{
			if (!args[i + 1])
				return (error_return(sh, too_few_args, NULL));
			info->output_file = ft_strdup(args[i + 1]);
			return (redirect_output(env_info, info, path));
		}
		i++;
	}
	return (true);
}

int		find_redirection(char *args[])
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<"))
			return (i);
		i++;
	}
	return (0);
}

int		check_redirections(char *args[], t_env *env_info, char *path)
{
	int			i;
	int			count_args;
	t_redirect	*info;

	i = 0;
	count_args = 0;
	if ((count_args = find_redirection(args)))
	{
		if (!(info = (t_redirect *)ft_memalloc(sizeof(t_redirect))))
			error_exit(sh, mem_alloc_err);
		if (!(info->args = ft_memalloc(sizeof(char *) * (count_args + 1))))
			error_exit(sh, mem_alloc_err);
		while (args[i])
		{
			if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<"))
				break;
			info->args[i] = ft_strdup(args[i]);
			i++;
		}
		if (check_params(env_info, args, info, path))
			return (clean_info(info, path));
	}
	return (0);
}
