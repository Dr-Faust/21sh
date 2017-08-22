/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 16:01:08 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 16:23:32 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			prompt_flag(int flag)
{
	static int	prompt;

//	ft_printf("flag = %d\n", flag);
	if (flag)
		prompt = flag;
//	ft_printf("prompt = %d\n", prompt);
	return (prompt);
}

static void	handle_sigint(int *signal)
{
	int		prompt;

	prompt = prompt_flag(0);
	if (prompt == 42)
	{
		ft_putchar('\n');
		write_prompt();
	}
	*signal = 0;
	ft_memdel((void **)&g_line);
	if (!(g_line = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	if (g_quote_line)
	{
		ft_memdel((void **)&g_quote_line);
		if (!(g_quote_line = ft_strnew(1)))
			error_exit(sh, mem_alloc_err);
	}
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
		handle_sigint(&signal);
	else if (signal == SIGWINCH)
	{
		ioctl(0, TIOCGWINSZ, &win_size);
		g_win_size = win_size.ws_col;
	}
	return ;
}

void		manage_signals(void)
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
}
