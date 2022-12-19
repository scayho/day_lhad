/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:18:15 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/18 12:02:10 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_evar_value(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->e_name))
			return (env->e_value);
		env = env->next;
	}
	return (NULL);
}

int	arg_len(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	remove_path(void)
{
	char	**tmp;

	tmp = g_var.paths;
	while (*tmp)
		free(*tmp++);
	free(g_var.paths);
	g_var.paths = NULL;
}

void	display_with_declare(t_env *p)
{
	while (p)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((p->e_name), 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd((p->e_value), 1);
		ft_putstr_fd("\n", 1);
		p = p->next;
	}
}

int	valid_export(char *s)
{
	char	*p;

	p = NULL;
	p = ft_strchr(s, '=');
	if (!p || s[0] == '=' || s[0] == '+')
	{
		if (!p && !ft_strchr(s, '+'))
			return (0);
		ft_putstr_fd("invalid identifier\n", 2);
		return (0);
	}
	if (*(p - 1) == '+' && *(p - 2) == '+')
	{
		ft_putstr_fd("invalid identifier\n", 2);
		return (0);
	}
	if (!ft_isalnum(*(p - 1)) && *(p - 1) != '+')
	{
		ft_putstr_fd("invalid identifier\n", 2);
		return (0);
	}
	return (1);
}

void	err_malloc_msg(void)
{
	ft_putstr_fd("Error occur with allocation\n", 2);
}

// n9ass lines
char	**get_cmd_arg_size(char *buf)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != ' ')
		i++;
	ret = malloc(sizeof (char *) * 2);
	if (!ret)
		return (err_malloc_msg(), NULL);
	ret[0] = malloc (i);
	if (!ret[0])
		return (err_malloc_msg(), free(ret), NULL);
	while (is_space(buf[i]) && buf[i])
		i++;
	while (buf[i++])
		j++;
	ret[1] = malloc (j + 1);
	if (!ret[1])
		return (err_malloc_msg(), free(ret[0]), free(ret), NULL);
	return (ret);
}

char	**cmd_arg(char *buf)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = get_cmd_arg_size(buf);
	if (!ret)
		return (NULL);
	while (buf[i] && buf[i] != ' ')
	{
		ret[0][i] = buf[i];
		i++;
	}
	ret[0][i] = '\0';
	while (is_space(buf[i]) && buf[i])
		i++;
	while (buf[i])
		ret[1][j++] = buf[i++];
	ret[1][j] = '\0';
	return (ret);
}

char	*get_pwd_evar(t_env *p)
{
	if (!p)
		return (NULL);
	while (p)
	{
		if (!ft_strncmp("PWD", p->e_name, 4))
			return (p->e_value);
		p = p->next;
	}
	return (NULL);
}

char	*get_less_pwd_evar(t_env *p)
{
	char	*s;
	int		i;

	i = 0;
	if (!p)
		return (NULL);
	while (p)
	{
		if (!ft_strncmp("PWD", p->e_name, 4))
		{
			s = ft_strdup(p->e_value);
			while (s[i])
				i++;
			while (s[i] != '/')
				i--;
			s[i] = '\0';
			return (s);
		}
		p = p->next;
	}
	return (NULL);
}

void	get_pre_dir(void)
{
	char	*tmp;
	int		i;

	i = 0;
	while (g_var.pwd[i])
		i++;
	if (g_var.pwd[i - 1] == '/')
		i--;
	while (g_var.pwd[i] != '/')
		i--;
	g_var.pwd[i] = '\0';
	tmp = ft_strdup(g_var.pwd);
	g_var.pwd[i] = 'l';
	free(g_var.pwd);
	g_var.pwd = ft_strdup (tmp);
	free(tmp);
}

void	 join_err_pwd(char *dir)
{
	char	*r;
	int		i;
	int		j;

	i = ft_strlen(g_var.err_pwd);
	j = ft_strlen(dir);
	if (g_var.err_pwd[i - 1] != '/')
		r = malloc ((i + j + 2) * sizeof(char));
	else
		r = malloc ((i + j + 1) * sizeof(char));
	if (!r)
	{
		perror(r);
		return ;
	}
	ft_memcpy(r, g_var.err_pwd, i);
	if (g_var.err_pwd[i - 1] != '/')
		r[i++] = '/';
	r[i] = 0;
	r = join_free(r, dir);
	free(g_var.err_pwd);
	g_var.err_pwd = r;
}

int	count_backing(char *dir)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (dir[i])
	{
		if ((dir[i] && dir[i] == '.') && (dir[i + 1] == '.' && dir[i + 1])
			&& ((dir[i + 2] == '/' && dir[i + 2]) || !dir[i + 2]))
		{
			count++;
			i += 3;
		}
		else if ((dir[i] && dir[i] == '.')
			&& ((dir[i + 1] && dir[i + 1] == '/') || !dir[i + 1]))
			i += 2;
	}
	return (count);
}
