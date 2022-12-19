/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:04:05 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/17 20:04:06 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

// cat <<""'    '""ko<<""''"'" < zidan

int	first_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|' && !is_quoted(s, s + i))
			return (i);
		i++;
	}
	return (-1);
}

int	pipe_first(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && is_space(buf[i]))
		i++;
	if (buf[i] == '|')
		return (1);
	return (0);
}

int	pipe_syntax(char *buf)
{
	int	i;

	i = 0;
	if (pipe_first(buf))
		return (1);
	while (first_pipe(buf + i) != -1)
	{
		i += first_pipe(buf + i) + 1;
		while (buf[i] && is_space(buf[i]))
			i++;
		if ((buf[i] == '<' && buf[i + 1] == '<')
			|| (buf[i] == '>' && buf[i + 1] == '>'))
			i += 2;
		else if (buf[i] == '>')
			i++;
		else if (buf[i] == '<')
			return (1);
		if (!is_there_file(buf + i))
			return (1);
	}
	return (0);
}

int	redirection_syntax(char *buf)
{
	int	i;

	i = 0;
	while (first_redirection(buf + i) != -1)
	{
		i += first_redirection(buf + i);
		if ((buf[i] == '>' && buf[i + 1] == '>')
			|| (buf[i] == '<' && buf[i + 1] == '<'))
		{
			if (!is_there_file(buf + i + 2))
				return (1);
			i += 2;
		}
		else if (buf[i] == '>' || buf[i] == '<')
		{
			if (!is_there_file(buf + i + 1))
				return (1);
			i++;
		}
	}
	return (0);
}
