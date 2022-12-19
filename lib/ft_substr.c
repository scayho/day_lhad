/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:42:54 by hchahid           #+#    #+#             */
/*   Updated: 2022/08/30 18:32:52 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s)
		return (NULL);
	if ((start >= ft_strlen(s)) || len == 0)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	p = (char *)malloc((len + 1) * sizeof(char ));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		p[i++] = s[start++];
	p[i] = '\0';
	// printf(">>>>> %zu\n", len);
	return (p);
}
