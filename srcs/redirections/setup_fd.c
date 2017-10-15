#include "minishell.h"

void	set_heredoc_fd(t_pipe *p)
{
	pipe (p->fds);
	ft_putstr_fd(p->r->heredoc_line, p->fds[STDOUT_FILENO]);
	close (p->fds[1]);
	// p->input = p->fds[0];
	if (p->fds[0] != STDIN_FILENO)
		 dup2(p->fds[0], STDIN_FILENO);
	close(p->fds[0]);
	ft_memdel((void **)&p->r->heredoc_line);
}

void 	set_pipe_fd(t_pipe *p)
{
	if (p->fds[0] != STDIN_FILENO)
	{
		dup2(p->fds[0], STDIN_FILENO);
		close(p->fds[0]);
	}
	if (p->fds[1] != STDOUT_FILENO)
	{
		dup2(p->fds[1], STDOUT_FILENO);
		close(p->fds[1]);
	}
}

int 	set_single_otuput_fd(char **args, int index)
{
	int		fd;

	ft_memdel((void **)&args[index]);
	index++;
	if (!args[index])
		return (error_return(sh, too_few_args, "single_output"));
	fd = open(args[index], O_WRONLY | O_TRUNC | O_CREAT, 0664); 
	dup2(fd, STDOUT_FILENO); 
	close(fd);
	ft_memdel((void **)&args[index]);
	return (0);
}

int 	set_double_otuput_fd(char **args, int index)
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

int 	set_input_fd(char **args, int index)
{
	int		fd;

	ft_memdel((void **)&args[index]);
	index++;
	if (!args[index])
		return (error_return(sh, too_few_args, "input"));
	fd = open(args[index], O_RDONLY, 0600);  
	dup2(fd, STDIN_FILENO);
	close(fd);
	ft_memdel((void **)&args[index]);
	return (0);
}