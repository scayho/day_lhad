/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nested_dirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:22:49 by hchahid           #+#    #+#             */
/*   Updated: 2022/09/23 12:01:48 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_dir(char **dir)
{
    char    *ret;
    char    *tmp;
	char	*d;
    int     len;
    int     i;

    i = 0;
	d = *dir;
    len = ft_strlen(d);
    while (d[i] && d[i] != '/')
        i++;
	i ++;
    ret = malloc(i + 1);
    if (!ret)
        return (NULL);
    i = 0;
    while (d[i] && d[i] != '/')
    {
        ret[i] = d[i];
        i++;
    }
	ret[i] = d[i];
	i++;
    ret[i] = '\0';
    tmp = malloc(len - i + 1);
    if (!tmp)
        perror(tmp);
    len = 0;
    while (d[i])
        tmp[len++] = d[i++];
    tmp[len] = '\0';
    free(d);
    *dir = tmp;
    return (ret);
}

void    cut_pre_dir(char **dir)
{
    char    *ret;
	char	*d;
    int     j;
    int     i;

    i = 0;
    j = 0;
	d = *dir;
	if (!d)
		return ;
    while (d[i])
        i++;
    if (d[i - 1] == '/')
        i -= 2;
    while (d[i] != '/')
        i--;
    ret = malloc (i + 1);
    if (!ret)
	{
		perror (ret);
        return ;
	}
    while (j < i)
    {
        ret[j] = d[j];
        j++; 
    }
    ret[j] = '\0';
    free(d);
    *dir = ret;
}

void    join_dir(char **dir, char *first)
{
    char    *tmp;

	if (!*dir)
		return ;
	tmp = join_free(*dir, "/");
    tmp = join_free(tmp, first);
    // free(*dir);
    *dir  = tmp;
}

int    try_dir(char *dir)
{
    char    *tmp;
    char    *first;
    char    *p;
    // int     i;

    // i = 0;
	printf("dir = %s\n", dir);
	p = ft_strdup(dir);
    tmp = ft_strdup(g_var.pwd);
    while (ft_strlen (p))
    {
        first = get_dir(&p);
		printf("first = %s\n", first);
		printf("dup_p = %s\n", p);
        if (!ft_strcmp(first, "../") || !ft_strcmp(first, ".."))
            cut_pre_dir(&tmp);
        else if (!ft_strcmp(first, "./") || !ft_strcmp(first, "."))
            ;
        else
		{
            join_dir(&tmp, first);
			printf("the one gone too = %s\n", tmp);
			if (chdir(tmp))
			{
				free(tmp);
				free(p);
				printf("No such file or directory\n");
				return (1);
			}
		}
    }
    // if (!chdir(tmp))
    // {
    //     free(g_var.pwd);
    //     g_var.pwd = ft_strdup (tmp);
	// 					printf("******* %s *******\n", g_var.pwd );
    // }
	free(tmp);
	free(p);
	return (0);
}

void	retrieving_err()
{
	ft_putstr_fd("error retrieving current directory: ",2);
	ft_putstr_fd("getcwd cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}
