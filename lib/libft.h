/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:37:22 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/18 18:02:00 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
#include "paths.h"

typedef struct s_star
{
	char			*buf;
	char			*arg;
	int				index;
	bool			is_rediraction;
}	t_star;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_line
{
	char			*line;
	struct s_line	*next;
}	t_line;

typedef struct s_arg
{
	char			*arg;
	bool			linked;
	bool			redirection;
	struct s_arg	*next;
}	t_arg;

typedef struct s_fd
{
	int	in;
	int	out;
	int	rest;
}	t_fd;

typedef struct s_env
{
	char			*e_name;
	char			*e_value;
	struct s_env	*next;
}	t_env;

typedef struct s_var
{
	char	**paths;
	char	*err_pwd;
	char	*pwd;
	int		exit_status;
}	t_var;

t_var	g_var;
t_arg	*last_arg(t_arg *lst);
int		add_back_arg(t_arg **lst, t_arg *new);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

void	check_exit_status(int pid);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_atoi(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(const char *s);
int		ft_isprint(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);

int		ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *e_var, int check);
// t_env	*ft_lstnew(char *e_var);
t_env	*ft_lstlast(t_env *lst);
int		ft_lstsize(t_env *lst);
void	del(t_env **env_p, t_env *var);
void	mid_end(t_env **env_p, t_env *var);

void	ft_lstadd_front(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *str, char c);

char	*get_e_var_value(char *value);
char	*get_e_var_name(char *s);
void	remove_path(void);
int		valid_export(char *s);

#endif
