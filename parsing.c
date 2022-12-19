/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:34:21 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/17 18:15:26 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == ' ' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_there_file(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (0);
	while (is_space(s[i]) && s[i])
		i++;
	if (s[i] && (s[i] == '<' || s[i] == '>' || s[i] == '|'))
		return (0);
	return (1);
}
