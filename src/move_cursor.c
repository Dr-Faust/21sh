/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 17:51:08 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/23 21:31:47 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_term_len(int prompt_len, int *position)
{
	int		len;

	len  = win_size.ws_col - prompt_len;
	if ((*position) == len)
		ft_putchar('\n');
	ft_putstr(tgetstr("nd", 0));
	(*position)++;
}

void		move_left(char *buf, char *buffer, int *position)
{
	if (buf[2] == LEFT && (*position) > 0)
	{
		ft_putstr(tgetstr("le", 0));
		(*position)--;
	}
	else if (buf[3] == LEFT && (*position) > 0)
	{
		while (buffer[(*position) - 1] == ' ' && (*position) > 0)
		{
			ft_putstr(tgetstr("le", 0));
			(*position)--;
		}
		while (buffer[(*position) - 1] != ' ' && (*position) > 0)
		{
			ft_putstr(tgetstr("le", 0));
			(*position)--;
		}
	}
	else if (buf[2] == START && (*position) > 0)
		while (*position > 0)
		{
			ft_putstr(tgetstr("le", 0));
			(*position)--;
		}
}

void		move_right(char *buf, char *buffer, int *position, int prompt_len)
{
	if (buf[2] == RIGHT && buffer[(*position)])
		check_term_len(prompt_len, position);
	else if (buf[3] == RIGHT && buffer[(*position)])
	{
		while (buffer[(*position)] != ' ' && *position < (int)ft_strlen(buffer))
			check_term_len(prompt_len, position);
		while (buffer[(*position)] == ' ' && *position < (int)ft_strlen(buffer))
			check_term_len(prompt_len, position);
	}
	else if (buf[2] == END && buffer[(*position)])
		while (buffer[(*position)])
			check_term_len(prompt_len, position);
}
