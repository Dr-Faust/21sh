/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 15:53:54 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/06 15:53:57 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, char c)
{
	char	*str;
	int		len;

	len = 0;
	while (s1[len] != c && s1[len])
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	str = ft_strncpy(str, s1, len);
	return (str);
}
