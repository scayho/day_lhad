/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:24:17 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/17 19:51:12 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

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

int	is_quoted(char *s, char *mark)
{
	char	quote;
	int		i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && (s + i) > mark)
			return (0);
		else if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
			{
				if ((s + i) == mark)
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	isthereredirection(t_arg *s)
{
	t_arg	*iter;

	iter = s;
	while (iter)
	{
		if (iter->redirection)
			return (1);
		iter = iter->next;
	}
	return (0);
}

int	first_redirection(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
		if ((s[i] == '<' || s[i] == '>') && !is_quoted(s, s + i))
			return (i);
		i++;
	}
	return (-1);
}

int	redirection_count(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (first_redirection(s + i) != -1)
	{
		i += first_redirection(s + i);
		while (s[i] && (s[i] == '<' || s[i] == '>'))
			i++;
		count++;
	}
	return (count);
}

char	*redirection_name(char *buf)
{
	int		i;
	char	*name;
	int		start;

	i = 0;
	while (buf[i] != 1 && buf[i])
		i++;
	if (buf[i] == 1)
		start = ++i;
	while (buf[i] != 1 && buf[i])
		i++;
	if (buf[i] == 1)
	{
		buf[i] = '\0';
	}
	name = ft_strdup(buf + start);
	return (name);
}

// end 2 means exlude redirection and delemeter 
// end 0 means exclude only rederaction and remove special character
char	*exclude_name1(char *str, int start, int i, char *new)
{
	str[start] = '\0';
	start++;
	i = start;
	while (str[start] != 1 && str[start])
		start++;
	if (str[start] == 1)
		str[start] = ' ';
	while (str[start] != 1 && str[start])
		start++;
	if (str[start] == 1)
		str[start] = ' ';
	new = ft_strdup(str);
	new = ft_strjoin(new, " ");
	new = ft_strjoin(new, str + i);
	return (new);
}

char	*exlude_name(char	*str, int start, int end)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	if (end == 2)
	{
		str[start] = '\0';
		start++;
		while (str[start] != 1 && str[start])
			start++;
		start++;
		while (str[start] != 1 && str[start])
			start++;
		new = ft_strdup(str);
		new = ft_strjoin(new, str + start + 1);
	}
	else if (end == 0)
		new = exclude_name1(str, start, i, new);
	free(str);
	return (new);
}

int	first_heredoc(char *s, int hd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
		if ((s[i] == '<' && s[i + 1] == '<') && !is_quoted(s, s + i))
			return (i);
		else if ((s[i] == '<' && s[i + 1] != '<' && s[i - 1] != '<')
			&& !is_quoted(s, s + i) && hd == 2)
			return (i);
		i++;
	}
	return (-1);
}

int	outputcheck(char *s, int hd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
		if ((s[i] == '>' && s[i + 1] == '>') && !is_quoted(s, s + i))
			return (i);
		else if ((s[i] == '>' && s[i + 1] != '>' && s[i - 1] != '>')
			&& !is_quoted(s, s + i) && hd == 2)
			return (i);
		i++;
	}
	return (-1);
}
