/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:05 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/19 01:06:21 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ffree(char **s)
{
	free(*s);
	*s = NULL;
}

char	**list_to_tab(t_env *env)
{
	t_env	*t;
	char	**tab;
	int		i;

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

void	nopath(char **splited)
{
	printf("\033[0;31m %s: No such file or directory\n", splited[0]);
	free_dp(splited);
	exit(127);
}

void	binaryfile(char **splited, t_env **env)
{
	char	**tab;

	tab = list_to_tab(*env);
	execve(splited[0], splited, tab);
	printf("\033[0;31m %s: No such file or directory\n", splited[0]);
	free_dp(splited);
	exit(127);
}

void	bin_in_thisdir(t_env **env, char **splited)
{
	char	**tb;
	char	*cmd;

	cmd = splited[0];
	splited[0] = ft_strjoin(g_var.pwd, "/");
	splited[0] = join_free(splited[0], cmd);
	tb = list_to_tab(*env);
	execve(splited[0], splited, tb);
	free(splited[0]);
	splited[0] = cmd;
}

void	checkforbinaries(char **splited)
{
	char	*cmd;
	char	*tmp;
	int		i;

	i = 0;
	tmp = splited[0];
	cmd = ft_strdup(splited[0]);
	// free(splited[0]);
	while (g_var.paths[i])
	{
		splited[0] = ft_strjoin(g_var.paths[i], cmd);
		execve(splited[0], splited, NULL);
		free(splited[0]);
		i++;
	}
	splited[0] = tmp;
	perror (cmd);
}

void	cmd(char *buf, t_env **env)
{
	char	**splited;

	buf = eraseqout(buf, markqout(buf));
	splited = ft_split(buf, ' ');
	if (!splited[0])
		exit(1);
	if (if_directory(splited[0]))
	{
		free_dp(splited);
		exit (126);
	}
	else
	{
		bin_in_thisdir(env, splited);
		if (splited[0][0] == '/')
			binaryfile(splited, env);
		if (!g_var.paths)
			nopath(splited);
		else
			checkforbinaries(splited);
	}
	free_dp(splited);
	exit(127);
}

void	check_exit_status(int pid)
{
	if (WIFEXITED(g_var.exit_status))
		g_var.exit_status = WEXITSTATUS(g_var.exit_status);
	else if (WIFSIGNALED(g_var.exit_status))
	{
		g_var.exit_status = WTERMSIG(g_var.exit_status);
		if (g_var.exit_status == SIGQUIT)
			printf("^\\[1] %d Quit\n", pid);
	}
}

int	istherepipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
		if (s[i] == '|' && !is_quoted(s, s + i))
			return (i);
		i++;
	}
	return (-1);
}

void	executables(char *buf, t_env **env_p)
{
	int	pid;

	g_var.exit_status = 0;
	pid = fork();
	if (pid == -1)
		printf("\033[0;31mUnable to create processe\n");
	else
	{
		if (pid == 0)
			cmd(buf, env_p);
		else
		{
			siginit();
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
	if (arg == NULL)
		dprintf(2, "args null \n");
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
	if (file)
		free(file);
	free(buf);
}

int	execute(char *buf, t_env **env_p)
{
	int	pipecheck;

	sigdefault();
	pipecheck = istherepipe(buf);
	if (pipecheck != -1)
	{
		do_pipe(buf, env_p);
		free(buf);
		return (0);
	}
	execute2(buf, env_p);
	siginit();
	return (0);
}

int	execute_pipe(char *buf, t_env **env_p)
{
	if (!built_in(buf, env_p, get_args(buf, env_p)))
		;
	else
		cmd(buf, env_p);
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
	{
		cmd(buf, env_p);
	}
	(void)file;
	free(buf);
	exit (0);
	return (0);
}
// n9ass lines

void	execute_redirection_extra(int pid, char *buf, t_env **env_p)
{
	if (pid == 0)
	{
		cmd(buf, env_p);
	}
	else
	{
		waitpid(pid, &(g_var.exit_status), 0);
		check_exit_status(pid);
	}
}

int	execute_redirection(char *buf, t_env **env_p, char *file)
{
	int	pid;

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
			execute_redirection_extra(pid, buf, env_p);
	}
	unlink(file);
	free(buf);
	return (0);
}

char	*join_list(t_arg *cmd)
{
	char	*buf;
	t_arg	*iter;

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
	return (buf);
}

void	init(t_env **env, char **envp)
{
	modify_attr();
	set_env_vars(envp, env);
	siginit();
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

int	main(int ac, char **av, char **envp)
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
		system("leaks minishell");
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
		execute(empty_string(buf), &env_p);
	}
}
