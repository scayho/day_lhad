/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:38:20 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/17 14:58:43 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	quoted_space(char *s, int i)
{
	if (is_space(s[i]) && !is_quoted(s, s + i))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	still_in_name(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	closing_quote(char *line, char quote, int i)
{
	while (line[i] != quote)
		i++;
	i++;
	return (i);
}

int	quoted_heredoc(char *s, int i)
{
	if (s[i] == '<' && !is_quoted(s, s + i))
		return (1);
	return (0);
}
