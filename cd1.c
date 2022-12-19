/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:33:07 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/17 16:41:42 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	directory_err_cases(char *pwd, char *dir)
{
	if(!pwd && (!ft_strcmp("../", dir) || 
				!ft_strcmp("./", dir) ||
					!ft_strcmp("..", dir) || !ft_strcmp(".", dir)))
		return (1);
	return (0);
}

void	false_dir(char *old_pwd, char *new_pwd, char **splited, t_env **env_p)
{
	if (!(g_var.err_pwd))
		g_var.err_pwd = ft_strdup(g_var.pwd);
	if (!ft_strcmp("./", splited[1]) || !ft_strcmp(".", splited[1]))
		current_directory_error(old_pwd, new_pwd, splited, env_p);
	else
		previous_directory_error(old_pwd, new_pwd, splited, env_p);
}
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
