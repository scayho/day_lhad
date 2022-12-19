/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:42:23 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/17 14:25:04 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(char *s)
{
	int	i;

	i = 1;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	fecho(char **s, t_arg *arg)
{
	int	flag;

	flag = 0;
	(void)s;
	arg = arg->next;
	while (arg)
	{
		if (!flag && (arg->arg[0] == '-') && check_option(arg->arg))
		{
			flag = 1;
			arg = arg->next;
			continue ;
		}
		else
		{
			ft_putstr_fd(arg->arg, STDOUT_FILENO);
			if (!arg->linked && arg->next)
				write(1, " ", 1);
		}
		arg = arg->next;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}

int		skip_echo_option(char *arg);
void	echo_with_n(char **splited, t_env **env_p);
void	echo_without_n(char **splited, t_env **env_p);

int	echo(char **splited, t_env **env_p, t_arg *arg)
{
	(void)arg;
	if (!ft_strncmp("-n", splited[1], ft_strlen(splited[1]) + 2)
		&& !skip_echo_option(splited[1]))
		echo_with_n(splited, env_p);
	else
		echo_without_n(splited, env_p);
	return (0);
}

int	skip_echo_option(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (arg[i] == '-')
		i++;
	else
		return (1);
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (0);
	return (1);
}

void	echo_with_n(char **splited, t_env **env_p)
{
	int	i;

	i = 1;
	(void)env_p;
	while (!ft_strncmp("-n", splited[i], ft_strlen(splited[i]) + 2)
		|| !skip_echo_option(splited[i]))
			i++;
	if (!splited[i])
		return ;
	while (splited[i])
	{
		printf("%s", splited[i++]);
		if (splited[i])
			printf(" ");
	}
}

void	echo_without_n(char **splited, t_env **env_p)
{
	int	i;

	i = 1;
	while (splited[i])
	{
		if (splited[i][0] == '$' )
			write_e_var(env_p, (splited[i++] + 1));
		else
			printf("%s", splited[i++]);
		if (splited[i])
			printf(" ");
	}
	printf("\n");
}

void	write_e_var(t_env **env_p, char *my_var)
{
	t_env	*iter;

	iter = *env_p;
	while (iter)
	{
		if (!ft_strncmp(my_var, iter->e_name,
				ft_strlen(my_var) + ft_strlen(iter->e_name)))
		{
			ft_putstr_fd(iter->e_value, 1);
			return ;
		}
		iter = iter->next;
	}
}
