/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:23:53 by hchahid           #+#    #+#             */
/*   Updated: 2021/11/15 21:27:52 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	// size_t	i;
	char	*ls;
	char	*ld;

	// i = 0;
	if (!src && !dst)
		return (0);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		ls = (char *)src + (len - 1);
		ld = (char *)dst + (len - 1);
		while (len--)
			*ld-- = *ls--;
	}
	return (dst);
}
