/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:00:43 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/18 15:55:53 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_env *env_p, char *splited)
{
	if (splited)
		printf("\033[0;31menv: %s: No such file or directory\n", splited);
	else
		display(env_p);
	return (0);
}

int	export(t_env **env_p, char **splited)
{
	int	i;

	i = 1;
	if (!splited[i])
		display_with_declare(*env_p);
	while (splited[i] && valid_export(splited[i]))
	{
		if (!does_env_exist(env_p, splited[i]))
			if (ft_lstadd_back(env_p, ft_lstnew(splited[i], 1)))
				return (0);
		i++;
	}
	return (0);
}

int	unset(t_env **env_p, char **splited)
{
	t_env	*iter;
	int		i;

	i = 1;
	iter = *env_p;
	while (splited[i])
	{
		if (!ft_strncmp(splited[i], "PATH", 5))
			remove_path();
		iter = *env_p;
		while (iter)
		{
			if (!ft_strcmp(iter->e_name, splited[i]))
			{
				del(env_p, iter);
				break ;
			}
			iter = iter->next;
		}
		i++;
	}
	return (0);
}
