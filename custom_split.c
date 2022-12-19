/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:16:29 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/17 14:19:09 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_args(char *f, int len)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (i < len)
	{
		if (f[i])
		{
			n++;
			while (f[i])
				i++;
		}
		i++;
	}
	return (n);
}

char	*stage_1(char *s, char c)
{
	char	*f;
	int		i;

	i = 0;
	f = ft_strdup(s);
	while (s[i])
	{
		if (s[i] == c && !is_quoted(s, &s[i]))
			f[i] = '\0';
		i++;
	}
	return (f);
}

char	**fstage(char **r, int len, char *p, int slen)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	r = malloc ((len + 1) * sizeof (char *));
	if (!r)
		return (NULL);
	while (++j < slen)
	{
		if (p[j])
		{
			r[i] = ft_strdup(p + j);
			if (!r[i++])
			{
				free_dp(r);
				return (NULL);
			}
			while (p[j])
				j++;
		}
	}
	free(p);
	r[i] = NULL;
	return (r);
}

char	**custom_split(char *s, char c)
{
	char	**r;
	char	*p;
	int		len;

	r = NULL;
	p = stage_1(s, c);
	len = n_args(p, ft_strlen(s));
	r = fstage(r, len, p, ft_strlen(s));
	return (r);
}
