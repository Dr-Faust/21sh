/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:19:55 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/10 11:17:51 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(int index)
{
	char	*error[1];

	error[0] = "21sh: allocation error";
	ft_printf("%s\n", error[index]);
	exit(EXIT_FAILURE);
}

int		error_return(int index, char *arg)
{
	char	*error[11];

	error[0] = "cd: HOME doesn't set\n";
	error[1] = "cd: OLDPWD doesn't set\n";
	error[2] = "cd: no such file or directory: ";
	error[3] = "cd: permission denied: ";
	error[4] = "21sh: no such file or directory: ";
	error[5] = "21sh: permission denied: ";
	error[6] = "setenv: too few arguments: setenv var_name value\n";
	error[7] = "setenv: too much arguments: setenv var_name value\n";
	error[8] = "setenv: not an identifier: ";
	error[9] = "unsetenv: too few arguments: unsetenv var_name\n";
	error[10] = "unsetenv: there is no such variable: ";
	ft_printf("%s", error[index]);
	if (arg)
		ft_printf("%s\n", arg);
	return (1);
}
