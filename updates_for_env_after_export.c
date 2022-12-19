/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates_for_env_after_export.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 21:13:16 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/19 00:01:47 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	slash_in_end(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	i--;
	if (path[i] == '/')
		return (1);
	return (0);
}

void	replace_path(char	*env_var)
{
	char	**tmp;
	char	*tmp1;
	int		i;

	i = -1;
	tmp = NULL;
	if (g_var.paths)
	{
		tmp = g_var.paths;
		while (*tmp)
			free(*tmp++);
		free(g_var.paths);
	}
	g_var.paths = ft_split(get_e_var_value(env_var), ':');
	while (g_var.paths[++i])
	{
		tmp1 = g_var.paths[i];
		if (!slash_in_end(g_var.paths[i]))
			g_var.paths[i] = ft_strjoin(g_var.paths[i], "/");
		free(tmp1);
	}
}

void	replace_value(t_env **env, char *compared_to, char *env_var)
{
	t_env	*iter;

	iter = *env;
	if (!ft_strcmp(compared_to, iter->e_name))
	{
		if (compared_to[ft_strlen(compared_to) + 1] == 1)
		{
			iter->e_value = join_free(iter->e_value,
					get_e_var_value(env_var));
		}
		else
			change_env_value(iter, env_var);
		free(compared_to);
		return ;
	}
}

int	does_env_exist(t_env **env_p, char *env_var)
{
	t_env	*iter;
	char	*compared_to;
	char	**tmp;

	tmp = NULL;
	iter = *env_p;
	compared_to = get_e_var_name(env_var);
	if (compared_to[ft_strlen(compared_to) - 1] == '+')
	{
		compared_to[ft_strlen(compared_to) - 1] = 0;
		compared_to[ft_strlen(compared_to) + 1] = 1;
	}
	if (!ft_strncmp(compared_to, "PATH", 5))
		replace_path(env_var);
	while (iter)
	{
		replace_value(&iter, compared_to, env_var);
		iter = iter->next;
	}
	free(compared_to);
	return (0);
}

void	change_env_value(t_env *env, char *value)
{
	int	i;

	i = 0;
	free(env->e_value);
	while (value[i] && value[i] != '=')
		i++;
	i++;
	env->e_value = ft_strdup(value + i);
}
