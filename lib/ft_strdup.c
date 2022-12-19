/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:43:14 by hchahid           #+#    #+#             */
/*   Updated: 2022/09/22 15:15:15 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*c;
	char	*p;

	i = 0;
	p = (char *)s1;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	c = malloc((i + 1) * sizeof(char));
	if (!c)
		return (0);
	i = 0;
	while (p[i])
	{
		c[i] = p[i];
		i++;
	}	
	c[i] = '\0';
	return (c);
}
