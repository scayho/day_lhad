/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 00:25:31 by hchahid           #+#    #+#             */
/*   Updated: 2021/11/23 10:24:05 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				r;
	unsigned char	*t;
	unsigned char	*d;

	i = 0;
	t = (unsigned char *)s1;
	d = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		r = t[i] - d[i];
		if (r != 0)
			return (r);
		i++;
	}
	return (0);
}
