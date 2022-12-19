/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:59:52 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/19 03:44:10 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#include "minishell.h"

int	builtin(char **buf, t_env **env_p, t_arg *arg)
{
	if (!ft_strcmp("echo", buf[0]))
		return (echo(buf, env_p, arg));
	else if (!ft_strcmp("cd", buf[0]))
		return (cd (buf, env_p));
	else if (!ft_strcmp("pwd", buf[0]))
		return (pwd(*env_p));
	else if (!ft_strcmp("env", buf[0]) || !ft_strcmp("/usr/bin/env", buf[0]))
		return (env (*env_p, buf[1]));
	else if (!ft_strcmp("export", buf[0]))
		return (export (env_p, buf));
	else if (!ft_strcmp("unset", buf[0]))
		return (unset (env_p, buf));
	else if (!ft_strcmp("exit", buf[0]))
	{
		release_e_var(env_p);
		exit(0);
	}
	return (1);
}

void	comnd(char **buf)
{
	char	**tmp;
	char	*cmd;
	int		i;

	i = 0;
	if (!buf[0])
		return ;
	if (if_directory(buf[0]))
		exit (126);
	else
	{
		if (!g_var.paths)
		{
			printf("\033[0;31m %s: No such file or directory\n", buf[0]);
			free_dp(buf);
			exit(127);
		}
		if (buf[0][0] == '/')
		{
			execve(buf[0], buf, NULL);
			printf("\033[0;31m %s: No such file or directory\n", buf[0]);
			free_dp(buf);
			exit(127);
		}
		else
		{
			cmd = ft_strdup(buf[0]);
			free(buf[0]);
			while (g_var.paths[i])
			{
				buf[0] = ft_strjoin(g_var.paths[i], cmd);
				execve(buf[0], buf, NULL);
				free(buf[0]);
				i++;
			}
			perror (cmd);
		}
	}
	tmp = buf;
	(void)*buf++;
	while (*buf)
		free(*buf++);
	free(tmp);
	exit (127);
}


// int	exec(char **buf, t_env **env_p)
// {
// 	// buf = replace_env(buf, env_p);
// 	g_var.exit_status = 0;
// 	if (!builtin(buf, env_p,))
// 		exit(EXIT_SUCCESS);
// 	else
// 		comnd(buf);
// 	return (0);
// }

void    pipe_it(t_fd fd_pipe, char *ag, t_env **env_p)
{
    int pid;
    int pipe_redi[2];
	char *file;
	bool inputFlag;
	bool	outputFlag;

	inputFlag = 0;
	outputFlag = 0;
	file = NULL;
	ag = ft_strtrim(ag, " ");
    pid = fork();
    if (pid < 0)
    {
        ft_putstr_fd("error\n", 2);
		g_var.exit_status = 1;
		return ;
    }
    if (pid == 0)
    {
		if (first_redirection(ag) != -1)
		{
			if (first_heredoc(ag, 2) != -1)
				inputFlag = 1;
			if (outputcheck(ag, 2) != -1)
				outputFlag = 1;
			file = exec_redirection_pipe(get_args(ag, env_p), &ag, env_p, pipe_redi);
		}
		close(fd_pipe.rest);
		if (!inputFlag)
			dup2(fd_pipe.in, 0);
		close (fd_pipe.in);
		if (!outputFlag)
			dup2(fd_pipe.out, 1);
		close (fd_pipe.out);
		execute_redirection_pipe(ag, env_p, file, get_args(ag, env_p));
    }
	else if (pid && first_redirection(ag) != -1)
	{
		file = get_file_names();
		sig_init();
		waitpid(pid, &(g_var.exit_status), 0);
		unlink(file);
		free(file);
		free(ag);
	}
	else
		free(ag);
	if (fd_pipe.out == -2)
	{
		waitpid(pid, &(g_var.exit_status), 0);
		check_exit_status(pid);
	}
}

void	pipe_loop(int **fd, int pnum, char **ag, t_env **env_p)
{
	t_fd	fd_pipe;
	int		i;

	i = 1;
	fd_pipe.in = -1;
	fd_pipe.out = fd[0][1];
	fd_pipe.rest = fd[0][0];
	pipe_it (fd_pipe, ag[0], env_p);
	close(fd[0][1]);
	while (i <= pnum)
	{
		fd_pipe.in = fd[i - 1][0];
		fd_pipe.out = fd[i][1];
		fd_pipe.rest = fd[i][0];
		pipe_it(fd_pipe, ag[i], env_p);
		close(fd[i - 1][0]);
		close(fd[i][1]);
		i++;
	}
	fd_pipe.in = fd[i - 1][0];
	fd_pipe.out = -2;
	fd_pipe.rest = fd[i - 1][1];
	pipe_it(fd_pipe, ag[i], env_p);
	close(fd[i - 1][0]);
	while (wait(NULL) != -1)
		;
}

int	do_pipe(char *p, t_env **env_p)
{
	char	**ag;
	int		**fd;

	ag = custom_split(p, '|');
	fd = prepare_pipe(ag);
	if (!fd)
		return (write(2, "Error preparing fd forking\n", 27));
	pipe_loop(fd, arg_len(ag) - 2, ag, env_p);
	free_fd(fd, ag);
	free_dp(ag);
	return (0);
}