/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_first.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 14:55:03 by opodolia          #+#    #+#             */
/*   Updated: 2017/07/03 20:22:07 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_first(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	ft_memdel((void **)&s1);
	return (str);
}
