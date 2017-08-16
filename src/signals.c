/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 16:01:08 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/16 20:29:05 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int			singleton_prompt(int data)
{
	static int    prompt;

	if (data)
		prompt = data;
	return (prompt);
}*/

void		signal_handle(int signal)
{
//	int    prompt;

//	prompt = singleton_prompt(0);
	if (signal == SIGINT)
	{
		ft_putchar('\n');

		signal = 0;
		g_sig_flag = 1;
	}
	else if (signal == SIGWINCH)
	{
		ioctl(0, TIOCGWINSZ, &win_size);
		g_win_size = win_size.ws_col;
	//	ft_printf("size = %d\n", g_win_size);
	}
	return ;
}

int			 manage_signal(void)
{
	if (signal(SIGINT, signal_handle) == SIG_ERR)
		signal_error(sh, err_sys, "SIGINT");
	else if (signal(SIGQUIT, signal_handle) == SIG_ERR)
		signal_error(sh, err_sys, "SIGQUIT");
	else if (signal(SIGWINCH, signal_handle) == SIG_ERR)
		signal_error(sh, err_sys, "SIGWINCH");
//	ft_printf("flag_0 = %d\n", g_sig_flag);
	return (g_sig_flag);
}
