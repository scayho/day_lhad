/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:39:43 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/17 14:33:47 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_line	*ft_lstnew_hdoc(char *line)
// {
// 	t_line	*new;

// 	new = NULL;
// 	new = malloc (sizeof (t_line));
// 	if (!new)
// 	{
// 		printf("\033[0;31mUnable to add enviroment variable due to malloc problem");
// 		return (NULL);
// 	}
// 	if (!*line)
// 		new->line = ft_strdup("");
// 	else
// 		new->line = ft_strdup(line);
// 	new->next = NULL;
// 	return (new);
// }


// t_line	*ft_lstlast_hdoc(t_line *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// void	ft_lstadd_back_hdoc(t_line **lst, t_line *new)
// {
// 	t_line	*iter;

// 	iter = *lst;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		ft_lstlast_hdoc(iter)->next = new;
// 	}	
// }


// void	free_heredoc(t_line *p)
// {
// 	t_line	*tmp;

// 	while (p)
// 	{
// 		tmp = p;
// 		p = p->next;
// 		free(tmp->line);
// 		free(tmp);
// 	}
// }

// void	write_in_hdfile(t_line *p, int fd)
// {
// 	t_line	*iter;

// 	iter = p;
// 	while (iter)
// 	{
// 		ft_putstr_fd(iter->line, fd);
// 		ft_putstr_fd("\n", fd);
// 		iter = iter->next;
// 	}
// }

// void	create_f_hoc(t_line *p)
// {
// 	int	fd;

// 	fd = open (".heredoc.txt", 0777);
// 	if (fd == -1)
// 	{
// 		printf("issue opening heredoc file\n");
// 		return ;
// 	}
// 	write_in_hdfile(p, fd);
// 	while (get_next_line(fd));
// 	close(fd);
// }

// void	heredoc(char *name_out)
// {
// 	t_line	*p;
// 	char	line;

// 	line = NULL;
// 	p = NULL;
// 	while (1)
// 	{
// 		line = readline ("\033[0;37m> ");
// 		if (!line)
// 		{
// 			free_heredoc(p);
// 			return ;
// 		}
// 		if (!ft_strncmp(name_out, line, ft_strlen(name_out) + 1))
// 		{
// 			create_f_hoc(p);
// 			free_heredoc(p);
// 			return ;
// 		}
// 		else
// 			ft_lstadd_back_hdoc(&p, ft_lstnew_hdoc(line));
// 	}
// }