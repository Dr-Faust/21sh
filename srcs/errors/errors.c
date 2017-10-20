/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:19:55 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/28 17:28:34 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(t_command command_type, t_err_exit error_type)
{
	char	*error[2];
	char	*command[1];

	command[0] = "21sh: ";
	error[0] = "allocation error";
	error[1] = "error setting up terminal";
	ft_printf("%s", CYAN);
	ft_putstr_fd(command[command_type], STDERR_FILENO);
	ft_printf("%s", RED);
	ft_putstr_fd(error[error_type], STDERR_FILENO);
	ft_printf("%s", DEF);
	exit(EXIT_FAILURE);
}

void	set_commands_and_errors_arr(char *command[], char *error[])
{
	command[0] = "21sh: ";
	command[1] = "cd: ";
	command[2] = "env: ";
	command[3] = "setenv: ";
	command[4] = "unsetenv: ";
	error[0] = "HOME doesn't set\n";
	error[1] = "OLDPWD doesn't set\n";
	error[2] = "no such file or directory: ";
	error[3] = "permission denied: ";
	error[4] = "command not found: ";
	error[5] = "too few arguments: ";
	error[6] = "too much arguments: ";
	error[7] = "not an identifier: ";
	error[8] = "there is no such variable: ";
	error[9] = "error calling fork";
	error[10] = "incorrect parameter: ";
	error[11] = "child process couldn't be created\n";
}

char	*correct_errors(t_command command_type, t_err_ret error_type, char *arg)
{
	if (command_type == 3 && (error_type == 5 || error_type == 6))
		arg = "usage: [setenv var_name value]";
	else if (command_type == 4 && error_type == 5)
		arg = "usage: [unsetenv var_name]";
	else if (command_type == 2 && error_type == 5 &&
		!ft_strcmp(arg, "single_output"))
		arg = "usage: [env > arg]";
	else if (command_type == 2 && error_type == 5 &&
		!ft_strcmp(arg, "double_output"))
		arg = "usage: [env >> arg]";
	else if (command_type == 0 && error_type == 5 &&
		!ft_strcmp(arg, "single_output"))
		arg = "usage: [command > arg]";
	else if (command_type == 0 && error_type == 5 &&
		!ft_strcmp(arg, "double_output"))
		arg = "usage: [command >> arg]";
	else if (command_type == 0 && error_type == 5 &&
		!ft_strcmp(arg, "input"))
		arg = "usage: [command < arg]";
	else if (command_type == 0 && error_type == 5 &&
		!ft_strcmp(arg, "heredoc"))
		arg = "usage: [command << marker]";
	return (arg);
}

int		error_return(t_command command_type, t_err_ret error_type, char *arg)
{
	char	*error[12];
	char	*command[5];

	arg = correct_errors(command_type, error_type, arg);
	set_commands_and_errors_arr(command, error);
	ft_printf("%s", CYAN);
	ft_putstr_fd(command[command_type], STDERR_FILENO);
	ft_printf("%s", RED);
	ft_putstr_fd(error[error_type], STDERR_FILENO);
	ft_printf("%s", DEF);
	if (arg)
		ft_printf("%s\n", arg);
	return (1);
}

int		signal_error(t_command command_type, t_sig_err error_type, char *arg)
{
	char	*error[2];
	char	*command[1];

	command[0] = "21sh: ";
	error[0] = "signal interception impossible: ";
	error[1] = "received signal: ";
	ft_printf("%s", CYAN);
	ft_putstr_fd(command[command_type], STDERR_FILENO);
	ft_printf("%s", RED);
	ft_putstr_fd(error[error_type], STDERR_FILENO);
	ft_printf("%s", DEF);
	if (arg)
		ft_printf("%s\n", arg);
	return (1);
}
