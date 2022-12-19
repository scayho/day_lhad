/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:26:27 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/18 16:05:28 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **splited, t_env **env_p)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*pwd;
	
	old_pwd = NULL;
	new_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!splited[1])
		return (cd_home(env_p, old_pwd, new_pwd));
	pwd = getcwd(NULL, 0);
	if(directory_err_cases(pwd, splited[1]))
	{
		chdir(g_var.pwd);
		if (errno == EACCES)
			return (e_acces(splited[1], new_pwd, old_pwd, env_p));
		else
			false_dir(old_pwd, new_pwd, splited, env_p);
	}
	else
		valid_cd(new_pwd, old_pwd, splited[1], env_p);
	free(pwd);
	return (0);
}

int	cd_home(t_env **env_p, char *old_pwd, char *new_pwd)
{
	new_pwd = extract_evar_value(*env_p, "HOME");
	if (!new_pwd)
		return (free(old_pwd), ft_putstr_fd("cd: HOME not set\n", STDOUT_FILENO), 0);
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

void	current_directory_error(char *old_pwd, char *new_pwd,
	char **splited, t_env **env_p)
{
	free(old_pwd);
	old_pwd = ft_strdup(g_var.err_pwd);
	join_err_pwd(splited[1]);
	new_pwd = ft_strdup(g_var.err_pwd);
	update_pwd_env(env_p, old_pwd, new_pwd);
	free(new_pwd);
	free(old_pwd);
	retrieving_err();
}

void	previous_directory_error(char *old_pwd, char *new_pwd,
	char **splited, t_env **env_p)
{
	free(old_pwd);
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
		return ;
	}
	new_pwd = ft_strdup(g_var.err_pwd);
	update_pwd_env(env_p, old_pwd, new_pwd);
	free(new_pwd);
	free(old_pwd);
	retrieving_err();
}

void	valid_cd(char *new_pwd, char *old_pwd, char *dir, t_env **env_p)
{
	if (chdir(dir))
		perror(dir);
	else
	{
		new_pwd = getcwd(NULL, 0);
		free(g_var.pwd);
		g_var.pwd = getcwd(NULL, 0);
		update_pwd_env(env_p, old_pwd, new_pwd);
		free(new_pwd);
	}
	free(old_pwd);
}
