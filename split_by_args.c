/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 19:47:55 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/18 17:41:09 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "minishell.h"

t_arg	*last_arg(t_arg *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	delete_arg(t_arg *p)
{
	t_arg	*iter;

	while (p)
	{
		iter = p;
		p = p->next;
		free(iter->arg);
		free(iter);
	}
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	wildcardcheck(t_arg *r, t_arg *node)
{
	t_arg	*iter;
	int		check;

	check = 0;
	iter = r;
	if (!r)
		return (check);
	if (!node->linked)
		return (1);
	if (node->linked && !ft_strcmp(node->arg, ""))
	{
		while (iter->next != node)
			iter = iter->next;
		check = wildcardcheck(r, iter);
	}
	else if (node->linked && ft_strcmp(node->arg, ""))
		return (check);
	if (!check)
		return (check);
	return (1);
}

// t_arg	*new_arg(char *arg, char linked)

int	after_star(t_star s)
{
	int	i;

	i = s.index + 1;
	while (s.buf[i])
	{
		if (is_empty(s.buf + i))
			i += 2;
		else if (is_space(s.buf[i]))
			return (1);
		else
			return (0);
	}
	return (1);
}

char	*new_arg_sq(char *arg)
{
	char	*tmp;

	if (arg[0] == '\'')
	{
		tmp = arg;
		arg = ft_substr(arg, 1, ft_strlen(arg) - 2);
		free(tmp);
	}
	return (arg);
}

char	*new_arg_dq(char *arg, t_env **env_p, t_star s, t_arg *r)
{
	char	*tmp;

	if (arg[0] == '"')
	{
		tmp = arg;
		arg = ft_substr(arg, 1, ft_strlen(arg) - 2);
		free(tmp);
		arg = replace_env(arg, env_p);
	}
	else
	{
		if (!ft_strcmp(arg, "*") && wildcardcheck(r, last_arg(r))
			&& after_star(s))
		{
			arg = full_replace_env(arg, env_p);
		}
		else
		{
			arg = replace_env(arg, env_p);
		}
	}
	return (arg);
}

t_arg	*new_arg(t_env **env_p, t_arg *r, t_star s, char linked)
{
	t_arg	*new;
	char	*arg;

	(void)env_p;
	arg = s.arg;
	new = malloc (sizeof(t_arg));
	if (!new || !arg)
		return (new);
	new->linked = linked;
	new->redirection = s.is_rediraction;
	if (arg[0] == '\'' || is_redirection(arg[0]))
		arg = new_arg_sq(arg);
	else
		arg = new_arg_dq(arg, env_p, s, r);
	new->arg = arg;
	new->next = NULL;
	return (new);
}

int	add_back_arg(t_arg **lst, t_arg *new)
{
	t_arg	*iter;

	iter = *lst;
	if (!new)
		return (1);
	if (*lst == NULL)
		*lst = new;
	else
	{
		last_arg(iter)->next = new;
	}
	return (0);
}

int	quoted_redirection(char *s, int i)
{
	if ((s[i] == '<' || s[i] == '>') && !is_quoted(s, s + i))
		return (1);
	return (0);
}

int	end_of_arg(char *s)
{
	char	hold;
	int		i;

	i = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		hold = s[i++];
		while (s[i] && s[i] != hold)
			i++;
		return (i);
	}
	while (s[i] && s[i] != '"' && s[i] != '\''
		&& !is_space(s[i]) && !is_redirection(s[i]))
		i++;
	if (s[i] == '"' || s[i] == '\'' || is_space(s[i]) || is_redirection(s[i]))
		i--;
	return (i);
}

int	end_of_name(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '>' || s[i] == '<')
		i++;
	while (is_space(s[i]))
			i++;
	while (s[i] && !quoted_space(s, i) && !quoted_redirection(s, i))
		i++;
	if (s[i])
		i--;
	return (i);
}

// t_arg	*last_arg(t_arg *lst);
// t_arg	*new_arg(char *arg, char type);
// int		add_back_arg(t_arg **lst, t_arg *new);

char	*new_name(char *name, int len)
{
	char	*r;
	int		i;

	i = 0;
	while (!name[i] && i < len)
				i++;
	if (i == len)
		return (ft_strdup(""));
	r = ft_strdup(name + i);
	while (name[i] && i < len)
		i++;
	while (i < len)
	{
		if (name[i])
		{
			r = join_free(r, name + i);
			while (name[i] && i < len)
				i++;
		}
		else
			i++;
	}
	return (r);
}

char	*empty_out(char *name)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(name);
	while (i < len)
	{
		if (i < len && name[i] == '\'')
		{
			name[i++] = 0;
			while (name[i] && name[i] != '\'')
				i++;
			name[i++] = 0;
		}
		if (i < len && name[i] == '"')
		{
			name[i++] = 0;
			while (name[i] && name[i] != '"')
				i++;
			name[i++] = 0;
		}
		if (i < len && name[i] != '"' && name[i] != '\'')
			i++;
	}
	return (new_name(name, len));
}

char	*set_up_name(char *buf, char *special_string)
{
	char	*name;
	char	*tmp;
	char	hold;
	int		i;

	i = 0;
	while (is_redirection(buf[i]))
				i++;
	hold = buf[i - 1];
	buf[i - 1] = 0;
	while (is_space(buf[i]))
		i++;
	name = ft_strdup(buf + i);
	tmp = name;
	name = empty_out(name);
	free(tmp);
	i = 0;
	while (buf[i])
		i++;
	buf[i++] = hold;
	buf[i] = 0;
	buf = join_free(buf, special_string);
	buf = join_free(buf, name);
	buf = join_free(buf, special_string);
	return (free(name), buf);
}

t_arg	*remove_qoutess(t_arg *comand)
{
	t_arg	*iter;
	char	special_string[2];

	iter = comand;
	special_string[0] = 1;
	special_string[1] = 0;
	while (iter)
	{
		if ((is_redirection(iter->arg[0])
				&& is_redirection(iter->arg[1]) && iter->arg[2])
			|| (is_redirection(iter->arg[0]) && iter->arg[1]))
			iter->arg = set_up_name(iter->arg, special_string);
		iter = iter->next;
	}
	return (comand);
}

// t_arg	*get_args(char *s, t_env **env)
// {
// 	t_arg	*r;
// 	int		check;
// 	t_star	star;
// 	int		i;

// 	i = 0;
// 	r = NULL;
// 	star.buf = s;
// 	while (s[i])
// 	{
// 		while (is_space(s[i]))
// 			i++;
// 		star.index = i;
// 		if (s[i] == '<' || s[i] == '>')
// 		{
// 			i += end_of_name(s + i);
// 			star.arg = ft_substr(s, star.index, i - star.index + 1);
// 			star.is_rediraction = 1;
// 			check = add_back_arg(&r, new_arg(env, r, star, 0));
// 		}
// 		else
// 		{
// 			i += end_of_arg(s + i);
// 			star.is_rediraction = 0;
// 			if (s[i + 1] && !is_space(s[i + 1]))
// 			{
// 				star.arg = ft_substr(s, star.index, i - star.index + 1);
// 				check = add_back_arg(&r, new_arg(env, r, star, 1));
// 			}
// 			else
// 			{
// 				star.arg = ft_substr(s, star.index, i - star.index + 1);
// 				check = add_back_arg(&r, new_arg(env, r, star, 0));
// 			}
// 		}
// 		if (check)
// 			return (delete_arg(r), NULL);
// 		if (!s[i])
// 			break ;
// 		i++;
// 	}
// 	return (remove_qoutess(r));
// }


t_arg	*get_args(char *s, t_env **env)
{
	t_arg	*r;
	int		check;
	int		index;
	t_star	star;
	int		i;

	i = 0;
	r = NULL;
	star.buf = s;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		index = i;
		star.index = i;
		if (s[i] == '<' || s[i] == '>')
		{
			i += end_of_name(s + i);
			star.arg = ft_substr(s, index, i - index + 1);
			star.is_rediraction = 1;
			check = add_back_arg(&r, new_arg(env, r, star, 0));
		}
		else
		{
			i += end_of_arg(s + i);
			star.is_rediraction = 0;
			if (s[i + 1] && !is_space(s[i + 1]))
			{
				star.arg = ft_substr(s, index, i - index + 1);
				check = add_back_arg(&r, new_arg(env, r, star, 1));
			}
			else
			{
				star.arg = ft_substr(s, index, i - index + 1);
				check = add_back_arg(&r, new_arg(env, r, star, 0));
			}
		}
		if (check)
			return (delete_arg(r), NULL);
		if (!s[i])
			break ;
		i++;
	}
	r = remove_qoutess(r);
	return (r);
}
