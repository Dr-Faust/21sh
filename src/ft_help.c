/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 16:41:19 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/03 20:19:31 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_help(void)
{
	int			i;
	const char	*str[] =
	{"echo", "cd", "setenv", "unsetenv", "env", "help", "exit", 0};

	i = -1;
	ft_printf("\n%s%s%s%s%s\n", B_RED, "opodolia's ", B_BLUE, "minishell", DEF);
	ft_printf("Type program name and argument, and hit enter.\n");
	ft_printf("The following are built in:\n");
	while (str[++i])
		ft_printf("  %s\n", str[i]);
	ft_printf("Use the man command for information on other programs.\n");
	return (1);
}
