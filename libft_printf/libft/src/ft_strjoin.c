/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:48:08 by opodolia          #+#    #+#             */
/*   Updated: 2017/06/19 20:51:49 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s1 && s2)
		if ((str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			str = ft_strcat(str, s1);
			str = ft_strcat(str, s2);
			return (str);
		}
	return (0);
}
