/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:26:32 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/18 17:12:12 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	fill_path(char *path)
{
	char	*tmp;
	int		i;

	i = -1;
	g_var.paths = ft_split(path, ':');
	while (g_var.paths[++i])
	{
		tmp = g_var.paths[i];
		g_var.paths[i] = ft_strjoin(g_var.paths[i], "/");
		free(tmp);
	}
}

char	*update_shlvl(char	*old_value)
{
	char	*tmp;

	tmp = old_value;
	old_value = ft_itoa(ft_atoi(old_value) + 1);
	free(tmp);
	return (old_value);
}

t_env	*ft_lstnew(char *env_var, int check)
{
	t_env	*new;
	char	*tmp;

	tmp = NULL;
	new = malloc (sizeof (t_env));
	if (!new)
	{
		printf("\033[0;31mUnable to add env_var due to allocation issues\n");
		return (NULL);
	}
	new->e_name = get_e_var_name(env_var);
	if (!(new->e_name))
		return (NULL);
	tmp = ft_strchr(new->e_name, '+');
	if (tmp)
		*tmp = '\0';
	new->e_value = get_e_var_value(env_var);
	if (!(new->e_value))
		return (NULL);
	new->next = NULL;
	if (!ft_strncmp(new->e_name, "SHLVL", 5) && check == 0)
		new->e_value = update_shlvl(new->e_value);
	if (!ft_strncmp(new->e_name, "PATH", 5))
		fill_path(new->e_value);
	return (new);
}

	// printf("e_name = %s | e_value = %s\n", new->e_name, new->e_value);
	// if (!ft_strncmp(new->e_name, "SHLVL", 6))
	// {
	// 	new->e_value = ft_itoa(ft_atoi(ft_strdup(new->e_value)) + 1);
	// }