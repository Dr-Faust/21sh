/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:19:55 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/16 17:08:19 by opodolia         ###   ########.fr       */
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
	ft_printf("%s%s%s%s%s\n", CYAN, command[command_type],
		RED, error[error_type], DEF);
	exit(EXIT_FAILURE);
}

int		error_return(t_command command_type, t_err_ret error_type, char *arg)
{
	char	*error[11];
	char	*command[4];

	command[0] = "21sh: ";
	command[1] = "cd: ";
	command[2] = "setenv: ";
	command[3] = "unsetenv: ";
	error[0] = "HOME doesn't set\n";
	error[1] = "OLDPWD doesn't set\n";
	error[2] = "no such file or directory: ";
	error[3] = "permission denied: ";
	error[4] = "command not found: ";
	error[5] = "too few arguments: setenv var_name value\n";
	error[6] = "too much arguments: setenv var_name value\n";
	error[7] = "not an identifier: ";
	error[8] = "too few arguments: unsetenv var_name\n";
	error[9] = "there is no such variable: ";
	error[10] = "error calling fork";
	ft_printf("%s%s%s%s%s", CYAN, command[command_type],
		RED, error[error_type], DEF);
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
	ft_printf("%s%s%s%s%s", CYAN, command[command_type],
		RED, error[error_type], DEF);
	if (arg)
		ft_printf("%s\n", arg);
	return (1);
}
