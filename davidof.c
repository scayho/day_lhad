/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   davidof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:35:02 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/17 14:01:01 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	is_empty(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '"' && str[i + 1] == '"')
		return (1);
	else if (str[i] == '\'' && str[i + 1] == '\'')
		return (1);
	return (0);
}

int	hereco_before(char	*origin, char	*target)
{
	int	i;

	i = 0;
	while (target - i > origin)
	{
		while (!is_space(target[i]) && target - i > origin)
		{
			if (target[i] == '<' || target[i] == '>')
				return (1);
			i++;
		}
		while (is_space(target[i]) && target - i > origin + 1)
		{
			i++;
		}
		if ((target[i] == '<' && target[i - 1] == '<')
			|| target - i - origin < 2)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ignore_alpha(char *str, int dj)
{
	int	i;

	i = 1;
	while (str[i] != dj && str[i] != '\0')
		i++;
	return (i + 1);
}

char	*exclude_empty(char *buf, int i)
{
	char	*tmp;
	char	*tmp1;

	tmp = NULL;
	tmp1 = NULL;
	buf[i] = '\0';
	tmp = ft_strdup(buf);
	tmp1 = ft_strdup(buf + i + 2);
	free(buf);
	buf = ft_strjoin(tmp, tmp1);
	free(tmp1);
	free(tmp);
	return (buf);
}

char	*empty_string2(char *buf, int i)
{
	while (buf[i])
	{
		if (is_empty(buf + i))
		{
			if (hereco_before(buf, buf + i - 1))
				i += 2;
			else if (!is_space(buf[i - 1]) && !is_space(buf[i + 2]))
				i += 2;
			else if (buf[i + 2] && !is_space(buf[i + 2])
				&& (buf[i] != '"' && buf[i] != '\''))
				buf = exclude_empty(buf, i);
			else
				buf = exclude_empty(buf, i);
		}
		else if (buf[i] == '"' || buf[i] == '\"')
		{
			if (buf[i] == '"')
				i += ignore_alpha(buf + i, '"');
			else if (buf[i] == '\'')
				i += ignore_alpha(buf + i, '\'');
		}
		else
			i++;
	}
	return (buf);
}

char	*empty_string(char	*buf)
{
	int	i;
	int	j;
	int	check;

	j = 0;
	i = 0;
	check = 0;
	if (is_empty(buf + i))
	{
		check = 1;
		i += 2;
	}
	buf = empty_string2(buf, i);
	if (check == 1)
		buf = exclude_empty(buf, 0);
	return (buf);
}
