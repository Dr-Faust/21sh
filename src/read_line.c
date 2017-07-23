/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/23 21:02:54 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_keys(char *buf, char *buffer, int *position, int prompt_len)
{
	if ((buf[2] == LEFT || buf[3] == LEFT || buf[2] == START)
		&& (*position) > 0)
		move_left(buf, buffer, position);
	else if ((buf[2] == RIGHT || buf[3] == RIGHT || buf[2] == END)
			&& buffer[(*position)])
		move_right(buf, buffer, position, prompt_len);
	else if ((buf[0] == BACKSPACE && (*position) > 0) ||
			(buf[2] == DELETE && buffer[(*position)]))
		buffer = del_char(buf, buffer, position);
	return (buffer);
}

static int	check_print_position(char *buf, char **buffer, int *position)
{
	if (buf[0] == '\n')
	{
		ft_printf("\n");
		*buffer = ft_strjoin_free_first(*buffer, "\n\0");
		return (1);
	}
	else if ((*position) < (int)ft_strlen(*buffer))
		*buffer = add_char(buf[0], *buffer, position);
	else
	{
		*buffer = ft_strjoin_free_first(*buffer, buf);
		ft_printf("%c", buf[0]);
	}
	(*position)++;
	return (0);
}

char		*read_line(int prompt_len)
{
	char		*buffer;
	char		buf[8];
	int			position;
	int			bytes;

	if (!(buffer = ft_strnew(1)))
		error_exit(sh, mem_alloc_err);
	position = 0;
	while (42)
	{
		ft_bzero(buf, 8);
		bytes = read(0, buf, 8);
	//	ft_printf("bytes = %d\n", bytes);
		if (bytes == 1 && (ft_isprint(buf[0]) || buf[0] == '\n'))
			if (check_print_position(buf, &buffer, &position))
				return (buffer);
		buffer = parse_keys(buf, buffer, &position, prompt_len);
	}
}
