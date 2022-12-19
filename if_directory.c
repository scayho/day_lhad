/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:55:07 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/17 14:35:25 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_directory(char	*buf)
{
	struct stat	st;

	stat(buf, &st);
	if (S_ISDIR(st.st_mode))
	{
		printf("%s: is a directory\n", buf);
		return (1);
	}
	return (0);
}
