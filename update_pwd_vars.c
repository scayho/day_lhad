/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:34:37 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/17 20:04:48 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_vars(char **env_value, char *new_value)
{
	char	*tmp;

	tmp = *env_value;
	*env_value = ft_strdup(new_value);
	free(tmp);
}
