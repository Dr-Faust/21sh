/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 19:22:15 by opodolia          #+#    #+#             */
/*   Updated: 2017/10/19 19:22:18 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_heredoc_fd(t_pipe *p)
{
	pipe(p->fds);
	ft_putstr_fd(p->r->heredoc_line, p->fds[STDOUT_FILENO]);
	ft_memdel((void **)&p->r->heredoc_line);
	close(p->fds[1]);
	p->input = p->fds[0];
	if (p->input != STDIN_FILENO)
		dup2(p->input, STDIN_FILENO);
	close(p->fds[0]);
}

void	set_pipe_fd(t_pipe *p)
{
	if (p->input != STDIN_FILENO)
	{
		dup2(p->input, STDIN_FILENO);
		close(p->input);
	}
	if (p->fds[1] != STDOUT_FILENO)
	{
		dup2(p->fds[1], STDOUT_FILENO);
		close(p->fds[1]);
	}
}

int		set_write_fd(char **args, int index, int io_fd)
{
	int		fd;

	ft_memdel((void **)&args[index]);
	index++;
	if (!args[index])
		return (error_return(sh, too_few_args, "single_output"));
	fd = open(args[index], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (io_fd == 1)
		dup2(fd, STDOUT_FILENO);
	else if (io_fd == 2)
		dup2(fd, STDERR_FILENO);
	close(fd);
	ft_memdel((void **)&args[index]);
	return (0);
}

int		set_append_fd(char **args, int index)
{
	int		fd;

	ft_memdel((void **)&args[index]);
	index++;
	if (!args[index])
		return (error_return(sh, too_few_args, "double_output"));
	fd = open(args[index], O_APPEND | O_RDWR | O_CREAT, 0664);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_memdel((void **)&args[index]);
	return (0);
}

int		set_read_fd(char **args, int index)
{
	int		fd;

	ft_memdel((void **)&args[index]);
	index++;
	if (!args[index])
		return (error_return(sh, too_few_args, "input"));
	fd = open(args[index], O_RDONLY, 0664);
	dup2(fd, STDIN_FILENO);
	close(fd);
	ft_memdel((void **)&args[index]);
	return (0);
}
