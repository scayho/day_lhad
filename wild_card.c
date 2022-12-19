/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:05:20 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/17 20:08:17 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	r = malloc ((i + j + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		r[i++] = s2[j++];
	r[i] = '\0';
	return (r);
}

char	*wildcard(void)
{
	struct dirent	*file_dir;
	char			*r;
	DIR				*dir;

	r = NULL;
	dir = opendir(".");
	if (!dir)
	{
		write(2, "Opendir issue\n", 14);
		return (NULL);
	}
	file_dir = readdir(dir);
	if (!file_dir)
		return (NULL);
	if (file_dir->d_name[0] != '.')
		r = ft_strjoin(file_dir->d_name, " ");
	else
		r = ft_strdup("");
	while (file_dir)
	{
		if (file_dir->d_name[0] != '.')
		{
			r = join_free(r, file_dir->d_name);
			r = join_free(r, " ");
		}
		file_dir = readdir(dir);
	}
	closedir(dir);
	return (r);
}
