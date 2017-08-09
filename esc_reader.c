/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 18:57:10 by opodolia          #+#    #+#             */
/*   Updated: 2017/08/09 19:04:16 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <term.h>

int			main(void)
{
	int				tty_fd;
	char			buf[8];
	struct termios	term;

	tty_fd = open("/dev/tty", O_RDWR);
	tcgetattr(tty_fd, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(tty_fd, TCSANOW, &term);
	while (1)
	{
		bzero(buf, sizeof(buf));
		read(1, buf, 8);
		printf("\033[2J\r");
		printf("%.2hhx %.2hhx %.2hhx %.2hhx %.2hhx %.2hhx %.2hhx %.2hhx \n", buf[0],
			buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
		printf(" %c  %c  %c  %c  %c  %c  %c  %c \n", buf[0], buf[1], buf[2], buf[3],
			buf[4], buf[5], buf[6], buf[7]);
		fflush(stdout);
	}
	return (0);
}
