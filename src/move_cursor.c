/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 17:51:08 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/22 19:41:17 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void		move_right(char *buf, char *buffer, int *position)
{
	if (buf[2] == RIGHT && buffer[(*position)])
	{
		ft_putstr(tgetstr("nd", 0));
		(*position)++;
	}
	else if (buf[3] == RIGHT && buffer[(*position)])
	{
		while (buffer[(*position)] != ' ' && *position < (int)ft_strlen(buffer))
		{
			ft_putstr(tgetstr("nd", 0));
			(*position)++;
		}
		while (buffer[(*position)] == ' ' && *position < (int)ft_strlen(buffer))
		{
			ft_putstr(tgetstr("nd", 0));
			(*position)++;
		}
	}
	else if (buf[2] == END && buffer[(*position)])
		while (buffer[(*position)])
		{
			ft_putstr(tgetstr("nd", 0));
			(*position)++;
		}
}
