/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 16:22:59 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/16 16:23:07 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &default_term);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0 ||
		(term.c_lflag & (ECHO | ICANON)) || term.c_cc[VMIN] != 1 ||
		term.c_cc[VTIME] != 0)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &default_term);
		error_exit(setup_term_err);
	}
}
