/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoutes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:44:34 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/17 18:53:11 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	markqout(char *buf)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(buf);
	while (i < len)
	{
		if (buf[i] == '\'')
		{
			buf[i] = '\0';
			while (buf[i] != '\'' && i < len)
				i++;
			buf[i] = '\0';
		}
		else if (buf[i] == '"')
		{
			buf[i] = '\0';
			while (buf[i] != '"' && i < len)
				i++;
			buf[i] = '\0';
		}
		else
			i++;
	}
	return (len);
}

int	loop_for_i(char *buf, int len, int i, int check)
{
	if (check == 1)
	{
		while (buf[i] == '\0' && i < len)
			i++;
	}
	else
	{
		while (buf[i] != '\0' && i < len)
			i++;
	}
	return (i);
}

char	*eraseqout(char *buf, int len)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp1;

	i = 0;
	tmp1 = "\0";
	tmp = NULL;
	i = loop_for_i(buf, len, i, 1);
	tmp = ft_strdup(buf + i);
	tmp1 = ft_strjoin(tmp1, tmp);
	free(tmp);
	i = loop_for_i(buf, len, i, 2);
	while (i < len)
	{
		i = loop_for_i(buf, len, i, 1);
		tmp = ft_strdup(buf + i);
		tmp2 = tmp1;
		tmp1 = ft_strjoin(tmp1, tmp);
		free(tmp);
		free(tmp2);
		i = loop_for_i(buf, len, i, 2);
	}
	return (tmp1);
}
