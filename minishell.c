/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:05 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/19 04:08:26 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ffree(char **s)
{
	free(*s);
	*s = NULL;
}

char	**list_to_tab(t_env *env)
{
	t_env *t;
	char	**tab;
	int i;

	i = 0;
	t = env;
	while (env)
	{
		i++;
		env = env->next;
	}
	tab = malloc (sizeof(char *) * i);
	if (!tab)
		exit(0);
	i = 0;
	while (t)
	{
		tab[i] = ft_strjoin(ft_strjoin(t->e_name, "="), t->e_value);
		i++;
		t = t->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	noPath(char **splited)
{
	printf("\033[0;31m %s: No such file or directory\n", splited[0]);
	free_dp(splited);
	exit(127);
}

void	binaryFile(char **splited, t_env **env)
{
	char	**tb;

	tb = list_to_tab(*env);
	execve(splited[0], splited, tb);
	execve(splited[0], splited, NULL);
	printf("\033[0;31m %s: No such file or directory\n", splited[0]);
	free_dp(splited);
	exit(127);
}

void	checkForBinaries(char **splited, t_env **env)
{
	char	**tb;
	char	*cmd;
	int		i;

	i = 0;
	cmd = ft_strdup(splited[0]);
	free(splited[0]);
	while (g_var.paths[i])
	{
		splited[0] = ft_strjoin(g_var.paths[i], cmd);
		execve(splited[0], splited, NULL);
		free(splited[0]);
		i++;
	}
	splited[0] = ft_strjoin(g_var.pwd, "/");
	splited[0] = join_free(splited[0], cmd);
	tb = list_to_tab(*env);
	execve(splited[0], splited, tb);
	perror (cmd);
}

char	**prepar_tb_cmd(t_arg *arg)
{
	t_arg	*iter;
	int		i;
	char	**tb;

	i = 0;
	iter = arg;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	tb = malloc (sizeof(char *) * i + 1);
	if (!tb)
		return (dprintf(2, "failed to allocate \n"), NULL);
	iter = arg;
	i = 0;
	while (iter)
	{
		tb[i] = eraseqout(iter->arg, markqout(iter->arg));
		iter = iter->next;
		i++;
	}
	tb[i] = NULL;
	delete_arg(arg);
	return (tb);
}

char	**remove_qoutes_splited(char	**buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		buf[i] = eraseqout(buf[i], markqout(buf[i]));
		if (!buf[i])
			return (NULL);
		i++;
	}
	return (buf);
}

// void	cmd(char *buf, t_env **env)
void	cmd(t_arg *arg, t_env **env)
{
	char	**splited;

	splited = joincmd(arg);
	splited = remove_qoutes_splited(splited);
	dprintf(2, "[[[%s]]]\n", splited[0]);
	if (!splited)
	{
		ft_putstr_fd("error allocation", 2);
		exit(1);
	}
	if (!splited[0])
		exit(1);
	if (if_directory(splited[0]))
	{
		free_dp(splited);
		exit (126);
	}
	else
	{
		if (!g_var.paths)
			noPath(splited);
		if (splited[0][0] == '/')
			binaryFile(splited, env);
		else
			checkForBinaries(splited, env);
	}
	free_dp(splited);
	exit(127);
}

int isTherePipe(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
        if (s[i] == '|'  && !is_quoted(s, s + i))
            return (i);
        i++;
    }
    return (-1);
}

void	executables(char *buf, t_env **env_p)
{
	int pid;

	g_var.exit_status = 0;
	pid = fork();
	if (pid == -1)
		printf("\033[0;31mUnable to create processe\n");
	else
	{
		if (pid == 0)
			cmd(get_args(buf, env_p), env_p);
		else
		{
			sig_init();
			waitpid(pid, &(g_var.exit_status), 0);
			check_exit_status(pid);
		}
	}
}

void	execute2(char *buf, t_env **env_p)
{
	t_arg	*arg;
	char	*file;

	file = NULL;
	arg = get_args(buf, env_p);
	if (isthereredirection(arg))
	{
		file = get_file_names();
		redirection(arg, buf, env_p);
	}
	else if (!built_in(buf, env_p, arg))
		;
	else
		executables(buf, env_p);
	unlink(file);
	free(file);
	free(buf);
}

int	execute(char *buf, t_env **env_p)
{
	int PipeCheck;

	sig_default();
	PipeCheck = isTherePipe(buf);
	if (PipeCheck != -1)
	{
		do_pipe(buf, env_p);
		free(buf);
		return(0);
	}
	execute2(buf, env_p);
	sig_init();
	return (0);
}

int	execute_pipe(char *buf, t_env **env_p)
{
	if (!built_in(buf, env_p, get_args(buf, env_p)))
		;
	else
		cmd(get_args(buf, env_p), env_p);
	free(buf);
	return (0);
}

int	execute_redirection_pipe(char *buf, t_env **env_p, char *file, t_arg *arg)
{
	if (!buf)
		return (0);
	if (!built_in(buf, env_p, arg))
		;
	else
		cmd(arg, env_p);
	(void)file;
	free(buf);
	exit (0);
	return (0);
}

int	execute_redirection(char *buf, t_env **env_p, char *file)
{
	int	pid;

	(void)file;
	if (!buf)
		return (0);
	if (!built_in(buf, env_p, get_args(buf, env_p)))
		;
	else
	{
		g_var.exit_status = 0;
		pid = fork();
		if (pid == -1)
			return (printf("\033[0;31mUnable to create processe\n"));
		else
		{
			if (pid == 0)
				cmd(get_args(buf, env_p), env_p);
			else
			{
				waitpid(pid, &(g_var.exit_status), 0);
				check_exit_status(pid);
			}
		}
	}
	unlink(file);
	// free(file);
	free(buf);
	return (0);
}

char *join_list(t_arg *cmd)
{
	char    *buf;
    t_arg   *iter;

    iter = cmd;
    if (!cmd)
        return (NULL);
	if (iter->linked)
		buf = ft_strdup(iter->arg);
	else 
    	buf = ft_strjoin(iter->arg, " ");
    iter = iter->next;
    while (iter)
    {
        buf = join_free(buf, iter->arg);
		if (!iter->linked && iter->next)
        	buf = join_free(buf, " ");
        if (!buf)
            return (NULL);
        iter = iter->next;
    }
    delete_arg(cmd);
    return (buf);
}

void	init(t_env **env, char **envp)
{
	modify_attr();
	set_env_vars(envp, env);
	sig_init();
}

int	syntax(char *buf)
{
	if (buf[0] == '\0')
		return (1);
	if (check_qotes(buf) == 0)
		return (1);
	if (redirection_syntax(buf) == 1)
		return (printf("redirection error\n"));
	if (pipe_syntax(buf) == 1)
		return (printf("pipe error\n"));
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_env				*env_p;
	char				*buf;

	(void)ac;
	(void)av;
	env_p = NULL;
	buf = NULL;
	init(&env_p, envp);
	while (1)
	{
		buf = readline ("\033[0;34m(minishell) : \033[0;37m");
		if (!buf)
		{
			release_e_var(&env_p);
			exit(0);
		}
		else if (*buf)
			add_history(buf);
		if (syntax(buf))
		{
			free(buf);
			continue ;
		}
		buf = empty_string(buf);
		execute(buf, &env_p);
		// system("leaks minishell");
	}
}
