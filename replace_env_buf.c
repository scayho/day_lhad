/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_buf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:33:26 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/18 01:35:10 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sub_str(char *s, int start, int end)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc (end - start + 1);
	if (!p)
		perror (p);
	while (start <= end)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

char	*remove_arg(char *buf, int start, int end)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc (ft_strlen(buf) - (end - start + 2));
	if (!ret)
		return (NULL);
	while (i < start - 1)
	{
		ret[i] = buf[i];
		i++;
	}
	j = i;
	i = end + 1;
	while (buf[i])
		ret[j++] = buf[i++];
	ret[j] = '\0';
	return (ret);
}

int	env_exist(t_env **env_p, char *name)
{
	t_env	*iter;

	iter = *env_p;
	if (!env_p || !iter)
		return (0);
	while (iter)
	{
		if (!ft_strcmp(name, iter->e_name))
			return (1);
		iter = iter->next;
	}
	return (0);
}

// char	*expand_it(char *buf, char *tmp, int start, int end, t_env **env_p)
char	*expand_it(char *buf, t_expnd c, t_env **env_p)
{
	char	*ret;
	char	*env;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	c.i--;
	env = extract_evar_value(*env_p, c.tmp);
	len = ft_strlen (buf) + c.i - c.index + 1 + ft_strlen (env);
	ret = malloc (len + 1);
	if (!ret)
		return (NULL);
	while (++i < c.index - 1)
		ret[i] = buf[i];
	while (env[j])
		ret[i++] = env[j++];
	j = c.i + 1;
	while (buf[j])
		ret[i++] = buf[j++];
	ret[i] = '\0';
	return (ret);
}

char	*replace_exstat_val(char *buf, int start, int finish)
{
	char	*r;

	buf[start] = 0;
	r = ft_strdup(buf);
	if (!r)
		return (perror(r), NULL);
	r = join_free(r, ft_itoa(g_var.exit_status));
	if (!r)
		return (perror(r), NULL);
	r = join_free(r, buf + finish);
	if (!r)
		return (perror(r), NULL);
	return (r);
}
// n9ass lines

// int	replace_env_in_buf(char **buf, char *tmp, t_env **env, int i)
// {
// 	char	*hold;

// 	hold = buf;
// 	buf = expand_it(buf, tmp, index, i - 1, env);
// 	i = index;
// 	i += ft_strlen(extract_evar_value(*env, tmp));
// 	free(hold);
// }

int	replace_exit_status(char **buf, int i)
{
	char	*hold;

	hold = *buf;
	*buf = replace_exstat_val(*buf, i, i + 2);
	i += ft_strlen(ft_itoa(g_var.exit_status));
	free(hold);
	return (i);
}

int	cut_false_env(char **buf, int i, int index)
{
	char	*hold;

	hold = *buf;
	*buf = remove_arg(*buf, index, i - 1);
	i = index - 1;
	free(hold);
	return (i);
}

int	is_there_exitstat_check(char *buf, int i)
{
	if (buf[i] == '$' && buf[i + 1] == '?'
		&& (!ft_isalnum(buf[i + 2]) || buf[i + 2] != '_'))
		return (1);
	return (0);
}

t_expnd	ds(int i, int index, char *tmp)
{
	t_expnd	s;

	s.i = i;
	s.index = index;
	s.tmp = tmp;
	return (s);
}

// void	init_expnd()

char	*replace_var(char *buf, t_expnd c, t_env **env)
{
	char	*hold;

	hold = NULL;
	c.i++;
	c.index = c.i;
	while (buf[c.i] && (ft_isalnum(buf[c.i]) || buf[c.i] == '_'))
		c.i++;
	c.tmp = sub_str(buf, c.index, c.i - 1);
	if (!c.tmp)
		return (perror(c.tmp), NULL);
	else if (env_exist(env, c.tmp))
	{
		hold = buf;
		buf = expand_it(buf, c, env);
		c.i = c.index;
		c.i += ft_strlen(extract_evar_value(*env, c.tmp));
		free(hold);
	}
	else
		c.i = cut_false_env(&buf, c.i, c.index);
	free(c.tmp);
	c.i -= 1;
	return (buf);
}

char	*replace_env(char *buf, t_env **env)
{
	t_expnd	c;

	c = ds(0, 0, NULL);
	while (buf[c.i])
	{
		if (is_there_exitstat_check(buf, c.i))
			c.i = replace_exit_status(&buf, c.i);
		if (buf[c.i] == '$' && buf[c.i + 1] && buf[c.i + 1] != ' ')
			buf = replace_var(buf, c, env);
		c.i++;
	}
	return (buf);
}

char	*replace_wild_card(char *buf, t_expnd c, char *wild)
{
	char	*wild_free;

	wild_free = buf;
	buf = ft_strjoin(buf, wild);
	free(wild_free);
	wild_free = buf;
	buf = ft_strjoin(buf, wild_free + c.i + 1);
	free(wild_free);
	return (buf);
}

char	*full_replace_env(char *buf, t_env **env)
{
	char	*wild;
	t_expnd	c;

	c = ds(0, 0, NULL);
	while (buf[c.i])
	{
		if (is_there_exitstat_check(buf, c.i))
			c.i = replace_exit_status(&buf, c.i);
		if (buf[c.i] == '$' && buf[c.i + 1] && buf[c.i + 1] != ' ')
			buf = replace_var(buf, c, env);
		if (buf[c.i] == '*' && c.i == 0
			&& (is_space(buf[c.i + 1]) || !buf[c.i + 1])
			&& !is_quoted(buf, &buf[c.i]))
		{
			wild = wildcard();
			buf[c.i] = '\0';
			buf = replace_wild_card(buf, c, wild);
			c.i += ft_strlen(wild);
			free(wild);
		}
		c.i++;
	}
	return (buf);
}
