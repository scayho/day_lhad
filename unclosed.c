/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:50:05 by hchahid           #+#    #+#             */
/*   Updated: 2022/09/02 18:56:06 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quotes(char *cmd)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39)
			flag++;
		i++;
	}
	if (flag % 2 == 0)
		return (1);
	printf("syntax error: Unclosed quotes\n");
	return (0);
}

int	unclosed_double_quotes(char *cmd)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34)
			flag++;
		i++;
	}
	if (flag % 2 == 0)
		return (1);
	printf("syntax error: Unclosed double quotes\n");
	return (0);
}

int	unclosed_parathesis(char *cmd)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i] == '(')
			flag++;
		else if (cmd[i] == ')')
			flag--;
		i++;
	}
	if (flag == 0)
		return (1);
	printf("syntax error: Unclosed paranthesis\n");
	return (0);
}

int	unclosed(char *s)
{
	if (!unclosed_double_quotes(s))
		return (1);
	else if (!unclosed_quotes(s))
		return (1);
	else if (!unclosed_parathesis(s))
		return (1);
	return (0);
}
