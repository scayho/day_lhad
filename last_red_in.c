/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_red_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:59:18 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/17 15:01:25 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	are_qouted(char *str, char *target)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (str[i] == '\'')
				i += ignore_alpha(str + i, '\'');
			else if (str[i] == '"')
				i += ignore_alpha(str + i, '"');
			if (str + i > target)
				return (1);
		}
		else
			if (str + i == target)
				return (0);
		i++;
	}
	return (0);
}

int	last_red_in(char *or, char *str)
{
	int	i;

	i = 0;
	while (str[i] == '<')
		i++;
	(void)or;
	while (str[i] != '\0')
	{
		if (str[i] == 1)
			i += ignore_alpha(str + i, 1);
		if (((str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
				|| (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')))
			return (1);
		i++;
	}
	return (0);
}
