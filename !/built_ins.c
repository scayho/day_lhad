/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:38:18 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/18 02:07:50 by abelahce         ###   ########.fr       */
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
// n9ass lines
char	**joincmd(t_arg *arg)
{
	char	**tab;
	t_arg	*iter;
	int		i;

	i = targ_size(arg);
	tab = malloc (sizeof(char *) * i + 1);
	if (!tab)
	{
		dprintf(2, "unable to malloc table in built_in\n");
		return (NULL);
	}
	i = 0;
	iter = arg;
	while (iter)
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
	tab[i] = NULL;
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
	return (delete_arg(arg), free_dp(splited), 1);
}

int	cd(char **splited, t_env **env_p)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*pwd;

	old_pwd = NULL;
	new_pwd = NULL;
	if (arg_len(splited) > 2)
	{
		printf("\033[0;31mcd: string not in pwd: %s\n", splited[1]);
		return (0);
	}
	old_pwd = getcwd(NULL, 0);
	if (!splited[1])
		return (cd_home(env_p, old_pwd, new_pwd));
	pwd = getcwd(NULL, 0);
	if(!pwd && (!ft_strcmp("../", splited[1]) || 
				!ft_strcmp("./", splited[1]) ||
					!ft_strcmp("..", splited[1]) || !ft_strcmp(".", splited[1])))
	{
		chdir(g_var.pwd);
		if (errno == EACCES)
			return (e_acces(splited[1], new_pwd, old_pwd, env_p));
		else
		{
			if (!(g_var.err_pwd))
				g_var.err_pwd = ft_strdup(g_var.pwd);
			if (!ft_strcmp("./", splited[1]) || !ft_strcmp(".", splited[1]))
			{
				old_pwd = ft_strdup(g_var.err_pwd);
				join_err_pwd(splited[1]);
				new_pwd = ft_strdup(g_var.err_pwd);
				update_pwd_env(env_p, old_pwd, new_pwd);
				free(new_pwd);
				free(old_pwd);
				retrieving_err();
			}
			else
			{			
				// if (new_pwd)
				// 	join_pwd(env_p, splited[1]);
				old_pwd = ft_strdup(g_var.err_pwd);
				join_err_pwd(splited[1]);
				get_pre_dir();
				if (!chdir(g_var.pwd))
				{
					free(g_var.err_pwd);
					g_var.err_pwd = NULL;
					new_pwd = ft_strdup(g_var.pwd);
					update_pwd_env(env_p, old_pwd, new_pwd);
					free(new_pwd);
					free(old_pwd);
					return (0);
				}
				new_pwd = ft_strdup(g_var.err_pwd);
				update_pwd_env(env_p, old_pwd, new_pwd);
				free(new_pwd);
				free(old_pwd);
				retrieving_err();
			}
		}
	}
	else
	{
		if (chdir(splited[1]))
			perror(splited[1]);
		else
		{
			new_pwd = getcwd(NULL, 0);
			if (!new_pwd)
			{
				free(old_pwd);
				free(new_pwd);
				free(pwd);
				printf("no such file or directory: %s\n", splited[1]);
				return (0);
			}
			free(g_var.pwd);
			g_var.pwd = getcwd(NULL, 0);
			update_pwd_env(env_p, old_pwd, new_pwd);
			free(new_pwd);
		}
		free(old_pwd);
	}
	free(pwd);
	return (0);
}

int	pwd(t_env *envp)
{
	char	*s;
	char	*p;

	if (g_var.err_pwd)
	{
		printf("%s\n", g_var.err_pwd);
		return (0);
	}
	else
	{
		printf("%s\n", g_var.pwd);
		return (0);
	}
	s = getcwd(NULL,0);
	if (!s)
	{
		p =  get_pwd_evar(envp);
		if (!p)
			perror(s);
		else
			printf("%s\n", p);
	}
	else
		printf("%s\n", s);
	free(s);
	return (0);
}

int	env(t_env *env_p, char *splited)
{
	if(splited)
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
			if (ft_lstadd_back(env_p, ft_lstnew(splited[i])))
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
