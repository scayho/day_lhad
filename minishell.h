/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:07 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/19 01:50:40 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include "lib/libft.h"
#include <sys/types.h>
#include <dirent.h>

#include <termios.h>
#include <errno.h>


#define RED \033[0;31m
#define GREEN \033[0;32m
#define YELLOW \033[0;33m
#define BLUE \033[0;34m
#define PURPLE \033[0;35m
#define WHITE \033[0;37m

typedef struct s_redi
{
    char	*name;
	int		i;
	int		next_heredoc;
	int	input1;
	int pid;
} t_redi;

typedef struct s_expnd
{
	int		index;
	int		i;
	char	*tmp;
} t_expnd;

char	**joincmd(t_arg *arg);
void	sig_init(void);
void	sig_default(void);
void	current_directory_error(char *old_pwd, char *new_pwd,char **splited, t_env **env_p);
void	previous_directory_error(char *old_pwd, char *new_pwd,char **splited, t_env **env_p);
void	valid_cd(char *new_pwd, char *old_pwd, char *dir, t_env **env_p);
int	directory_err_cases(char *pwd, char *dir);
void	false_dir(char *old_pwd, char *new_pwd, char **splited, t_env **env_p);

void ffree(char **s);
char *join_list(t_arg *cmd);
char    *eraseqout(char *buf, int len);
int    markqout(char    *buf);
// t_arg *get_args(char *s);
char	*full_replace_env(char *buf, t_env **env);
char	*exec_redirection_pipe(t_arg *command, char **buf, t_env **env_p, int *pip_redi);
int	execute_redirection_pipe(char *buf, t_env **env_p, char *file, t_arg *arg);
t_arg *get_args(char *s, t_env **env);
void    delete_arg(t_arg *p);
char    *wildcard();
int quoted_space(char *s, int i);
char    *expander(char *buf, t_env **env);
int	env_exist(t_env **env_p, char *name);
char *empty_string(char *buf);
int heredoc_name(char *buf, char *mark);
int     last_red_in(char *or, char    *str);
int	is_there_file(char *s);
int first_input(char *s);
int	ignore_alpha(char *str, int dj);
int are_qouted(char *str, char  *target);
int	check_qotes(char *str);


int outputcheck(char *s, int hd);


int redirection_syntax(char *buf);
int pipe_syntax(char *buf);
// char	*exlude_name(char	*str, int start, char *name);
char	*exlude_name(char	*str, int start, int end);
// char    *remove_qoutes(char *buf);
t_arg    *remove_qoutes(t_arg				*command);
int is_empty(char   *str);
char	*expand_it(char *buf, t_expnd c, t_env **env_p);
void	remove_path(void);
char	*remove_arg(char *buf, int start, int end);

/*-----------------------signals-----------------------*/
void	sighandle(int	sig);
void	siginit();
void	sigdefault();

/*-----------------------enviroment_variables---------------*/
void	set_env_vars(char **envp, t_env **env_p);
void	display(t_env *p);
char	*get_vars(char *s);
void	release_e_var(t_env **env_p);
/*-----------------------built_ins-----------------------*/
int		built_in(char *buf, t_env **env_p, t_arg *arg);
// int		built_in(char *buf, t_env **env_p);
/*-----------------------cd-----------------------*/
int		cd(char **splited, t_env **env_p);

int		e_acces(char *s, char *new_pwd, char *old_pwd, t_env **env_p);
int		cd_home(t_env **env_p, char *old_pwd, char *new_pwd);



int		pwd(t_env *env_p);
int		env(t_env *env_p, char *splited);
int		export(t_env **env_p, char **splited);
int		unset(t_env **env_p, char **splited);
int	fecho(char **s, t_arg *arg);
int		echo(char **splited, t_env **env_p, t_arg *arg);

// int		echo(char **splited, t_env **env_p);
/***********************************************************/


/*-----------------------parsing-----------------------*/

int	syntax_error(char *s);


/***********************************************************/

char *get_file_names(void);
void	write_e_var(t_env **env_p, char *my_var);

void	release_e_var(t_env **env_p);

void	redirection(t_arg *command, char *buf, t_env **env_p);

int	execute(char *buf, t_env **env_p);

// int	append_from_output(char **splited, t_env **env_p);

void	modify_attr();
int		if_directory(char	*buf);

int is_quoted(char *s, char *mark);

int	isthereredirection(t_arg *s);
char *join_list(t_arg *cmd);

int	execute_redirection(char *buf, t_env **env_p, char *file);
int	execute_pipe(char *buf, t_env **env_p);

void	mid_end_arg(t_arg **env_p, t_arg *var);
void	del_arg(t_arg **env_p, t_arg *var);
int	pwd_lenght(t_env **env_p);
void	update_pwd_env(t_env **env_p, char *old_pwd, char *new_pwd);
void	update_pwd_vars(char **env_value, char *new_value);
int	redirect_output(char *name, unsigned int open_flag);
char    **redirection_split(char *s);
char	*redirection_name(char *buf);
int first_redirection(char *s);
int first_heredoc(char *s, int hd);



int	does_env_exist(t_env **env_p, char *env_var);
void	change_env_value(t_env *env, char *value);

int	redirect_input(char *name);
int	heredoc(char *name);



char *extract_evar_value(t_env *env, char *name);
int	arg_len(char **s);

void	display_with_declare(t_env *p);
int	is_space(char c);
char	*get_pwd_evar(t_env *p);
char	*get_less_pwd_evar(t_env *p);
int	ft_strcmp(const char *s1, const char *s2);
char	*replace_env(char *buf, t_env **env);

int	rl_replace_line();

void	join_pwd(t_env **env, char *dir);
void	get_pre_dir();
void	join_err_pwd(char *dir);
int    try_dir(char *dir);

char	*join_free(char const *s1, char const *s2);

void	retrieving_err();

int	count_backing(char *dir);


void    cut_pre_dir(char **dir);



int is_quoted(char *s, char *mark);
char    **custom_split(char *s, char c);

/*--------------------pipe_utils------------------*/
void    free_dp(char **s);
void    free_fd(int **fd, char **ag);
int 	do_pipe(char *p, t_env **env_p);
int		**prepare_pipe(char **cmd);




#endif
