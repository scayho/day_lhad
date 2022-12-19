/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 04:50:55 by hchahid           #+#    #+#             */
/*   Updated: 2021/11/20 04:55:40 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(const char *set, char c)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*r;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i] && inset(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (i > start && inset(set, s1[i]))
		i--;
	end = i;
	r = malloc ((end - start + 2) * sizeof(char));
	if (!r)
		return (0);
	i = 0;
	while (start <= end)
		r[i++] = s1[start++];
	r[i] = '\0';
	return (r);
}
