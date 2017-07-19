/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:56:13 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/19 21:22:31 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *del_char(char *buf, char *buffer, int	*i)
{
	char	*ret;
	int		start;

	if (!(ret = ft_strnew(1)))
		error_exit(mem_alloc_err);
	start = 0;
	if (buf[0] == 127)
	{
		ret = ft_strjoin_free(ret, ft_strsub(buffer, start, (*i) - start - 1));
		start = *i;
	}
	else if (buf[2] == '3')
	{
		ret = ft_strjoin_free(ret, ft_strsub(buffer, start, (*i) - start));
		start = *i + 1;
	}
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start,
		ft_strlen(buffer) - start));
	ft_memdel((void **)&buffer);
	return (ret);
}

static char *add_char(char *buf, char *buffer, int *i)
{
	char	*ret;
	int		start;
	char	*print;

	if (!(ret = ft_strnew(1)))
		error_exit(mem_alloc_err);
	if (!(print = ft_strnew(1)))
		error_exit(mem_alloc_err);
	start = 0;
	ret = ft_strjoin_free(ret, ft_strsub(buffer, start, (*i) - start));
	print[0] = buf[0];
	start = *i;
	print = ft_strjoin_free(print, ft_strsub(buffer, start,
		ft_strlen(buffer) - start));
//	ft_printf("\nprint = %s\n", print);
	ft_putstr(tgetstr("sc", 0));
	ft_printf("%s", print);
	ft_putstr(tgetstr("rc", 0));
	ft_putstr(tgetstr("nd", 0));
	ret = ft_strjoin_free(ret, print);
	ft_memdel((void **)&buffer);
	return (ret);
}

static char	*parse_buf(char *buf, char *buffer, int *i)
{
	if (buf[2] == 'C' && buffer[(*i)])
	{
		ft_putstr(tgetstr("nd", 0));
		(*i)++;
	}
	else if (buf[2] == 'D' && (*i) > 0)
	{
		ft_putstr(tgetstr("le", 0));
		(*i)--;
	}
	else if (buf[0] == 127 && (*i) > 0)
	{
		ft_putstr(tgetstr("le", 0));
		ft_putstr(tgetstr("dc", 0));
		buffer = del_char(buf, buffer, i);
		(*i)--;
	}
	else if (buf[2] == '3' && buffer[(*i)])
	{
		ft_putstr(tgetstr("dc", 0));
		buffer = del_char(buf, buffer, i);
	}
/*	else if (buf[2] == 'H' && (*i) > 0)
	{
		ft_printf("%s", buf);
		*i = 0;
	}
	else if (buf[2] == 'F' && buffer[(*i)])
	{
		ft_printf("%s", buf);
		*i = ft_strlen(buffer) - 1;
	}
	ft_printf("%s", buf);*/
	return (buffer);
}

char		*read_line(void)
{
	char		*buffer;
	char		buf[8];
	static int	i;

	if (!(buffer = ft_strnew(1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (42)
	{
		ft_bzero(buf, 8);
		read(0, buf, 8);
		if ((ft_isprint(buf[0]) || buf[0] == '\n') && !buf[1] && buf[0] != 127)
		{
			if (i < (int)ft_strlen(buffer))
			{
				buffer = add_char(buf, buffer, &i);
			}
			else
			{
				buffer = ft_strjoin_free_first(buffer, buf);
				ft_printf("%c", buf[0]);
			}
			i++;

			if (buf[0] == '\n')
				return (buffer = ft_strjoin_free_first(buffer, "\0"));
		}
		else
			buffer = parse_buf(buf, buffer, &i);
	}
}
