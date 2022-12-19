/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:43:48 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/18 17:03:28 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_empty_env(t_env **env)
{
	char	*tmp;

	tmp = ft_strdup("PWD=");
	tmp = join_free(tmp, g_var.pwd);
	if (!tmp)
		return (perror(tmp));
	ft_lstadd_back(env, ft_lstnew(tmp, 1));
	free(tmp);
	tmp = ft_strdup("SHLVL=");
	tmp = join_free(tmp, "1");
	if (!tmp)
		return (perror(tmp));
	ft_lstadd_back(env, ft_lstnew(tmp, 1));
	free(tmp);
	tmp = ft_strdup("_=");
	tmp = join_free(tmp, "usr/bin/env");
	if (!tmp)
		return (perror(tmp));
	ft_lstadd_back(env, ft_lstnew(tmp, 1));
	free(tmp);
}

void	set_env_vars(char **envp, t_env **env_p)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_lstadd_back(env_p, ft_lstnew(envp[i++], 0));
	g_var.pwd = getcwd(NULL, 0);
	g_var.err_pwd = NULL;
	g_var.exit_status = 0;
	if (!envp[0])
	{
		fill_empty_env(env_p);
	}
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return ;
	while (s[i])
		write(1, &s[i++], 1);
}

void	display(t_env *p)
{
	while (p)
	{
		ft_putstr_fd((p->e_name), 1);
		ft_putstr("=");
		ft_putstr((p->e_value));
		ft_putstr("\n");
		p = p->next;
	}
}

char	*get_e_var_name(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	s[i] = '\0';
	ret = ft_strdup(s);
	s[i] = '=';
	return (ret);
}

char	*get_e_var_value(char *value)
{
	char	*ret;
	int		i;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	i++;
	ret = ft_strdup(value + i);
	return (ret);
}

void	release_e_var(t_env **env_p)
{
	t_env	*iter;
	t_env	*tmp;

	iter = *env_p;
	if (!env_p || !*env_p)
		return ;
	while (iter)
	{
		tmp = iter;
		iter = iter->next;
		free(tmp->e_name);
		free(tmp->e_value);
		free(tmp);
	}
}

void	update_pwd_env(t_env **env_p, char *old_pwd, char *new_pwd)
{
	t_env	*iter;

	iter = *env_p;
	if (!new_pwd || !old_pwd)
		return ;
	while (iter)
	{
		if (!ft_strncmp(iter->e_name, "PWD"
				, ft_strlen (iter->e_name) + ft_strlen("PWD")))
			update_pwd_vars(&(iter->e_value), new_pwd);
		else if (!ft_strncmp(iter->e_name, "OLDPWD"
				, ft_strlen (iter->e_name) + ft_strlen("OLDPWD")))
			update_pwd_vars(&(iter->e_value), old_pwd);
		iter = iter->next;
	}
}
