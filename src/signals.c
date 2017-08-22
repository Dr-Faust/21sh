/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 16:01:08 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/22 20:39:31 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			prompt_flag(int flag)
{
	static int	prompt;

	if (flag)
		prompt = flag;
	return (prompt);
}

static void	handle_sigint(int *signal)
{
	int		prompt;

	prompt = prompt_flag(0);
	if (prompt == 42)
	{
		ft_putchar('\n');
		g_info->prompt_len = write_prompt();
	}
	*signal = 0;
	ft_memdel((void **)&g_info->line);
	if (!(g_info->line = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	ft_memdel((void **)&g_info->bytes_str);
	if (!(g_info->bytes_str = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	g_info->position = g_info->prompt_len;
	g_info->line_index = 0;
	g_info->bytes_index = 0;
	if (g_info->quote_line)
	{
		ft_memdel((void **)&g_info->quote_line);
		if (!(g_info->quote_line = ft_strnew(1)))
			error_exit(sh, mem_alloc_err);
	}
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
		handle_sigint(&signal);
	else if (signal == SIGWINCH)
	{
		ioctl(0, TIOCGWINSZ, &g_info->win);
		g_info->win_size = g_info->win.ws_col;
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
