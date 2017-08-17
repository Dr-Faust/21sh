/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 16:01:08 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/17 18:15:05 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			singleton_prompt(int data)
{
	static int    prompt;

	if (data)
		prompt = data;
	return (prompt);
}

static void	signal_handler(int signal)
{
	int    prompt;

	prompt = singleton_prompt(0);
	if (signal == SIGINT)
	{
	//	ft_printf("here\n");
		signal = 0;
		if (prompt == 1)
			g_sig_flag = 1;
	}
	else if (signal == SIGWINCH)
	{
		ioctl(0, TIOCGWINSZ, &win_size);
		g_win_size = win_size.ws_col;
	}
	return ;
}

void		 manage_signal(void)
{
	struct sigaction	signal;

	signal.sa_handler = signal_handler;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &signal, 0) < 0)
		signal_error(sh, err_sys, "SIGINT");
//	else if (signal(SIGQUIT, signal_handle) == SIG_ERR)
//		signal_error(sh, err_sys, "SIGQUIT");
	else if (sigaction(SIGWINCH, &signal, 0) < 0)
		signal_error(sh, err_sys, "SIGWINCH");
//	ft_printf("flag_0 = %d\n", g_sig_flag);
}
