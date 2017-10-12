#include "minishell.h"

static int	check_path(char *path, char *arg)
{
	struct stat	buf;

	if ((lstat(path, &buf) != -1 && !S_ISREG(buf.st_mode))
		|| access(path, X_OK) != 0)
		return (error_return(sh, perm_denied, arg));
	return (0);
}

static char	*get_path(char *arg, t_env *env_info)
{
	if (env_info == 0)
		return (arg);
	while (env_info)
	{
		if (!ft_strcmp(env_info->name, "PATH"))
			break ;
		env_info = env_info->next;
	}
	if (env_info)
		return (verif_access(arg, env_info));
	else
		error_return(sh, no_s_f_or_dir, arg);
	return (0);
}

char		*treat_path(char **args, t_env *env_info)
{
	char	*path;

	path = 0;
	if (ft_strchr(args[0], '/') || env_info == 0)
	{
		if (access(args[0], F_OK) == 0)
			path = ft_strdup(args[0]);
		else
		{
			error_return(sh, no_s_f_or_dir, args[0]);
			return (NULL);
		}
	}
	path = (!path) ? get_path(args[0], env_info) : path;
	if (path && check_path(path, args[0]))
	{
		ft_memdel((void **)&path);
		return (NULL);
	}
	return (path);
}