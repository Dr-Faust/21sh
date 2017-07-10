/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 13:45:06 by opodolia          #+#    #+#             */
/*   Updated: 2017/03/29 13:53:27 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnchar(int len, char c)
{
	char	*str;

	if (!(str = ft_memalloc(sizeof(char) * (len + 1))))
		return ;
	while (len--)
		str[len] = c;
	write(1, str, ft_strlen(str));
	ft_memdel((void **)&str);
}
