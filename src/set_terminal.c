/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:33:54 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/07 21:08:15 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_terminal(void)
{
	struct termios	term;
	char			*terminal;

	tcgetattr(STDIN_FILENO, &default_term);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tgetflag("am"))
		ft_printf("exist\n");
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0 ||
		(term.c_lflag & (ECHO | ICANON)) || term.c_cc[VMIN] != 1 ||
		term.c_cc[VTIME] != 0 || !(terminal = getenv("TERM")))
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &default_term);
		tgetent(0, getenv("TERM"));
		error_exit(sh, setup_term_err);
	}
	else
		tgetent(0, terminal);
}
