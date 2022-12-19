/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:38:18 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/19 03:18:30 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	targ_size(t_arg *arg)
{
	t_arg	*iter;
	int		i;

	i = 0;
	iter = arg;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	return (i);
}

char	**create_double_pointer(int size)
{
	char	**tb;
	int		i;

	i = 0;
	tb = malloc (sizeof(char *) * size + 1);
	if (!tb)
		return (dprintf(2, "unable to malloc table in built_in\n"), NULL);
	while (i <= size)
		tb[i++] = NULL;
	return (tb);
}

char	**joincmd(t_arg *arg)
{
	char	**tab;
	t_arg	*iter;
	int		i;

	i = 0;
	iter = arg;
	tab = create_double_pointer(targ_size(arg));
	while (iter && tab)
	{
		tab[i] = ft_strdup(iter->arg);
		if (iter->linked && iter->next)
		{
			iter = iter->next;
			while (iter->linked && iter && iter->next)
			{
				tab[i] = join_free(tab[i], iter->arg);
				iter = iter->next;
			}
			tab[i] = join_free(tab[i], iter->arg);
		}
		iter = iter->next;
		i++;
	}
	return (tab);
}

int	built_in(char *buf, t_env **env_p, t_arg *arg)
{
	char	**splited;

	(void)buf;
	splited = joincmd(arg);
	if (!ft_strcmp("echo", splited[0]))
		return (fecho(splited, arg), free_dp(splited), delete_arg(arg), 0);
	else if (!ft_strcmp("cd", splited[0]))
		return (cd (splited, env_p), free_dp(splited), delete_arg(arg), 0);
	else if (!ft_strcmp("pwd", splited[0]))
		return (pwd(*env_p), free_dp(splited), delete_arg(arg), 0);
	else if (!ft_strcmp("env", splited[0])
		|| !ft_strcmp("/usr/bin/env", splited[0]))
		return (env (*env_p, splited[1]), free_dp(splited), delete_arg(arg), 0);
	else if (!ft_strcmp("export", splited[0]))
		return (export (env_p, splited), free_dp(splited), delete_arg(arg), 0);
	else if (!ft_strcmp("unset", splited[0]))
		return (unset (env_p, splited), free_dp(splited), delete_arg(arg), 0);
	else if (!ft_strcmp("exit", splited[0]))
	{
		free_dp(splited);
		delete_arg(arg);
		release_e_var(env_p);
		exit(0);
	}
	return (free_dp(splited), delete_arg(arg), 1);
}

int	pwd(t_env *envp)
{
	(void)envp;
	if (g_var.err_pwd)
		printf("%s\n", g_var.err_pwd);
	else
		printf("%s\n", g_var.pwd);
	return (0);
}
