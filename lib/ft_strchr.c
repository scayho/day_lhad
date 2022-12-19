/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:00:35 by hchahid           #+#    #+#             */
/*   Updated: 2021/11/20 00:05:01 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	b;

	i = 0;
	b = c;
	while (s[i])
	{
		if (b == s[i])
			return ((char *)&s[i]);
		i++;
	}
	if (b == s[i])
		return ((char *)&s[i]);
	return (0);
}
