/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:50:44 by hchahid           #+#    #+#             */
/*   Updated: 2022/10/31 17:44:08 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sign(int n, int *k)
{
	int	j;
	int	c;

	j = 1;
	c = n;
	while (c)
	{
		c = c / 10;
		j++;
	}
	*k = j - 1;
	if (n == 0)
		return ((char *)malloc (2 * sizeof(char )));
	if (n < 0)
	{
		*k += 1;
		return ((char *)malloc ((j + 1) * sizeof (char)));
	}
	else
		return ((char *)malloc (j * sizeof (char)));
	return (0);
}

char	*ft_itoa(int n)
{
	int				j;
	char			*p;
	unsigned int	m;

	if (n < 0)
		m = -n;
	else
		m = n;
	p = sign(n, &j);
	if (!p)
		return (NULL);
	p[j--] = '\0';
	while (m)
	{
		p[j--] = m % 10 + '0';
		m = m / 10;
	}
	if (n < 0)
		p[0] = '-';
	else if (n == 0)
	{
		p[0] = '0';
		p[1] = '\0';
	}
	return (p);
}
