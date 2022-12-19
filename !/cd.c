/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:27 by hchahid           #+#    #+#             */
/*   Updated: 2022/10/30 13:22:37 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	e_acces(char *s, char *new_pwd, char *old_pwd, t_env **env_p)
{
	if (!ft_strcmp("./", s) || !ft_strcmp(".", s))
	{
		perror(s);
		return (0);
	}
	free(old_pwd);
	old_pwd = ft_strdup(g_var.pwd);
	new_pwd = ft_strdup(g_var.pwd);
	cut_pre_dir(&new_pwd);
	if (access(new_pwd, X_OK))
	{
		perror(s);
		free(old_pwd);
		free(new_pwd);
		return (0);
	}
	get_pre_dir();
	chdir (g_var.pwd);
	free(new_pwd);
	new_pwd = ft_strdup(g_var.pwd);
	update_pwd_env(env_p, old_pwd, new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}

int	cd_home(t_env **env_p, char *old_pwd, char *new_pwd)
{
	new_pwd = extract_evar_value(*env_p, "HOME");
	if (!new_pwd)
		return (ft_putstr_fd("cd: HOME not set\n", STDOUT_FILENO), 0);
	else if (chdir(new_pwd))
	{
		if (old_pwd)
			free(old_pwd);
		return (0);
	}
	free(g_var.pwd);
	g_var.pwd = ft_strdup(new_pwd);
	if (g_var.err_pwd)
	{
		update_pwd_env(env_p, g_var.err_pwd, new_pwd);
		free(g_var.err_pwd);
		g_var.err_pwd = NULL;
	}
	else
	{
		update_pwd_env(env_p, old_pwd, new_pwd);
		free(old_pwd);
	}
	return (0);
}
