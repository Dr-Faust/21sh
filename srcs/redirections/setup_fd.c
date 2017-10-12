#include "minishell.h"

void 	set_pipe_fd(int *input, int *output)
{
	if (*input != STDIN_FILENO)
	{
		dup2(*input, STDIN_FILENO);
		close(*input);
	}
	if (*output != STDOUT_FILENO)
	{
		dup2(*output, STDOUT_FILENO);
		close(*output);
	}
}

int 	set_single_otuput_fd(char **args, int *i)
{
	int		fd;

	ft_memdel((void **)&args[*i]);
	(*i)++;
	if (!args[*i])
		return (error_return(sh, too_few_args, "single_output"));
	fd = open(args[*i], O_WRONLY | O_TRUNC | O_CREAT, 0664); 
	dup2(fd, STDOUT_FILENO); 
	close(fd);
	ft_memdel((void **)&args[*i]);
	return (0);
}

int 	set_double_otuput_fd(char **args, int *i)
{
	int		fd;

	ft_memdel((void **)&args[*i]);
	(*i)++;
	if (!args[*i])
		return (error_return(sh, too_few_args, "double_output"));
	fd = open(args[*i], O_APPEND | O_RDWR | O_CREAT, 0664); 
	dup2(fd, STDOUT_FILENO); 
	close(fd);
	ft_memdel((void **)&args[*i]);
	return (0);
}

int 	set_input_fd(char **args, int *i)
{
	int		fd;

	ft_memdel((void **)&args[*i]);
	(*i)++;
	if (!args[*i])
		return (error_return(sh, too_few_args, "input"));
	fd = open(args[*i], O_RDONLY, 0600);  
	dup2(fd, STDIN_FILENO);
	close(fd);
	ft_memdel((void **)&args[*i]);
	return (0);
}