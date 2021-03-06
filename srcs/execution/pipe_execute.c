/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 20:44:45 by opodolia          #+#    #+#             */
/*   Updated: 2017/10/19 20:44:46 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_child(t_pipe *p, pid_t pid)
{
	int		status;

	close(p->fds[1]);
	close(0);
	dup(p->fds[0]);
	close(p->fds[0]);
	if (!p->pipe_found)
	{
		waitpid(pid, &status, 0);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
}

void	check_pipes_redirections(char **args, t_pipe *p)
{
	if (p->pipe_found)
		close(p->fds[0]);
	if (p->pipe_found)
		set_pipe_fd(p);
	if (p->r->write_found)
		set_write_fd(args, p->r->write_index, 1);
	if (p->r->append_found)
		set_append_fd(args, p->r->append_index);
	if (p->r->read_found)
		set_read_fd(args, p->r->read_index);
	if (p->r->heredoc_found)
		set_heredoc_fd(p);
	if (p->r->output_fd_found)
		fd_aggregator(p, args);
}

int		launch(char **args, t_env *env_info, t_pipe *p, char *path)
{
	pid_t	pid;
	char	**env;
	int		i;
	char	*tmp;

	env = env_to_arr(env_info);
	if ((pid = fork()) == 0)
	{
		tmp = ft_strdup(args[0]);
		check_pipes_redirections(args, p);
		if (!ft_strcmp(args[0], tmp))
		{
			ft_strdel(&path);
			path = treat_path(args, env_info);
		}
		ft_strdel(&tmp);
		execve(path, args, env);
	}
	else if (pid < 0)
		error_return(sh, err_cal_fork, NULL);
	else
	{
		manage_child(p, pid);
		i = -1;
		while (env[++i])
			ft_memdel((void **)&(env[i]));
		ft_memdel((void **)&env);
		ft_memdel((void **)&path);
		if (p->r->heredoc_found)
			ft_memdel((void **)&p->r->heredoc_line);
	}
	return (1);
}

bool	pipe_builtin(char **args, t_env **env_info, t_pipe *p, t_hist *hist)
{
	int			i;
	bool		builtin_found;
	const char	*builtins_str[] = {"cd", "env", "setenv", "unsetenv", "help",
								"history"};

	i = -1;
	builtin_found = false;
	while (++i < 6)
		if (!ft_strcmp(args[0], builtins_str[i]))
		{
			builtin_found = true;
			if (p->fds[1] != STDOUT_FILENO)
			{
				dup2(p->fds[1], STDOUT_FILENO);
				close(p->fds[1]);
			}
			builtins_handler(args, env_info, hist);
		}
	return (builtin_found);
}

int		execute(t_pipe *p, t_env **env_info, t_hist **hist)
{
	int		i;
	char	**args;
	bool	builtin_found;
	char	*path;

	i = -1;
	p->input = STDIN_FILENO;
	while (++i < p->index)
	{
		pipe(p->fds);
		args = split_command(p->pipe_cmds[i]);
		builtin_found = pipe_builtin(args, env_info, p, *hist);
		if (builtin_found == false)
			if ((path = treat_path(args, *env_info)))
			{
				check_redirections(args, hist, p);
				launch(args, *env_info, p, path);
			}
		close(p->fds[1]);
		p->input = p->fds[0];
		clean_up(args);
		reset_flags(p);
	}
	p->pipe_found = false;
	return (main_execute(p, env_info, hist));
}
