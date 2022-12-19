/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:46:16 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/19 03:18:47 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	fake_herdoc(char	*delemeter)
{
	char	*string;

	string = readline("herdoc >: ");
	while (ft_strcmp(string, delemeter))
		string = readline("herdoc >: ");
}

void	herdoc(char	*delemeter, int fd)
{
	char	*string;

	string = readline("heredoc >: ");
	while (ft_strcmp(string, delemeter))
	{
		ft_putstr_fd(string, fd);
		ft_putstr_fd("\n", fd);
		string = readline("heredoc >:");
	}
}
// cat <<""'    '""ko<<""''"'" < zebzabi

void	extande_heredoc(char *buf)
{
	int		i;
	char	*name;

	i = 0;
	while (first_heredoc(buf, 1) != -1)
	{
		i = first_heredoc(buf, 1);
		name = redirection_name(ft_strdup(buf + i + 2));
		buf = exlude_name(buf, i, 2);
		fake_herdoc(name);
	}
}

char	*get_redi(t_arg *command)
{
	char	*buf;
	t_arg	*iter;

	iter = command;
	buf = ft_strdup("");
	while (iter)
	{
		if (iter->redirection)
		{
			buf = join_free(buf, iter->arg);
			buf = join_free(buf, " ");
			del_arg(&command, iter);
		}
		iter = iter->next;
	}
	return (buf);
}

// files_count it opens the directory and read all of it files
// count it and  return it
int	files_count(void)
{
	struct dirent	*file_dir;
	DIR				*dir;
	int				i;

	i = 0;
	dir = opendir("/tmp/");
	if (!dir)
	{
		write(2, "Opendir issue\n", 14);
		return (0);
	}
	file_dir = readdir(dir);
	if (!file_dir)
		return (0);
	while (file_dir)
	{
		file_dir = readdir(dir);
		i++;
	}
	closedir(dir);
	return (i);
}
// it open the directory and read all their files and list them
// in a 2D table

char	**get_dir_files(int i)
{
	struct dirent	*file_dir;
	DIR				*dir;
	int				j;
	char			**files;

	j = 0;
	dir = opendir("/tmp/");
	if (!dir)
	{
		write(2, "Opendir issue\n", 14);
		return (NULL);
	}
	files = malloc(sizeof(char *) * i + 1);
	if (!files)
	{
		dprintf(2, "tableau de file names not allocated\n");
		return (NULL);
	}
	file_dir = readdir(dir);
	while (file_dir)
	{
		files[j++] = file_dir->d_name;
		file_dir = readdir(dir);
	}
	return (files[j] = NULL, closedir(dir), files);
}

// it takes the 2D table that has the files names and check for
// .A if it exists it add A and keep looking until it finds a useable name
char	*get_right_file_names(char	**files, char *name)
{
	int		i;
	int		j;
	char	*extra;

	j = 0;
	i = 0;
	extra = ft_strdup("A");
	name = ft_strdup(".A");
	while (files[j])
	{
		if (ft_strcmp(files[j], name))
			j++;
		else
		{
			name = join_free(name, extra);
			i++;
			j = 0;
		}
	}
	free(extra);
	return (name);
}
// basicaly it reads all the files in the directory 
// check/generate heredoc files name
// in case of running multiple minishells

char	*get_file_names(void)
{
	char			*name;
	char			**files;
	int				i;
	char			*ex;

	name = NULL;
	i = files_count();
	files = get_dir_files(i);
	name = get_right_file_names(files, name);
	free(files);
	ex = name;
	name = ft_strjoin("/tmp/", name);
	free(ex);
	return (name);
}

// it exclude the redi nad its delemeter from the command
// and dup2 the output to the delemeter 

char	*exec_redi_pipe_output(char *cmd, int i)
{
	char	*name;

	name = NULL;
	if (cmd[i] == '>' && cmd[i + 1] == '>')
	{
		name = redirection_name(ft_strdup(cmd + i + 2));
		cmd = exlude_name(cmd, i, 2);
		redirect_output(name, O_APPEND);
		free(name);
	}
	else if (cmd[i] == '>')
	{
		name = redirection_name(ft_strdup(cmd + i + 1));
		cmd = exlude_name(cmd, i, 2);
		redirect_output(name, O_TRUNC);
		free(name);
	}
	return (name);
}

// it call for the remained heredoc and printf an error and quit

void	fail_exec_redi_pipe_input(char *cmd, int i, char *name)
{
	cmd = exlude_name(cmd, i, 0);
	extande_heredoc(cmd);
	dprintf(2, "%s\n", cmd);
	dprintf(2, "%s : no such file or directory\n", name);
	exit(1);
}

// it opens the delemeter if fail (call fail_exec_redi_pipe_impute)
// if good it exludes the the redi and its delemeter and dup the STDOUT

char	*exec_redi_pipe_input(char *cmd, int i)
{
	int		input1;
	int		next_heredoc;
	char	*name;

	name = redirection_name(ft_strdup(cmd + i + 1));
	next_heredoc = last_red_in(cmd, cmd + i);
	if (open(name, O_RDONLY) == -1)
		fail_exec_redi_pipe_input(cmd, i, name);
	else
		cmd = exlude_name(cmd, i, 2);
	if (!next_heredoc)
	{
		input1 = open(name, O_RDONLY, 0664);
		if (input1 < 0)
			;
		else if (dup2(input1, STDIN_FILENO) == -1)
		{
			dprintf(2, "failed to dup2 \n");
			exit(0);
		}
		close(input1);
	}
	free(name);
	return (cmd);
}

void	exec_redi_pipe_herdoc2(char	*name)
{
	int		input1;
	char	*file;

	file = get_file_names();
	input1 = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	herdoc(name, input1);
	close(input1);
	input1 = open(file, O_CREAT | O_RDWR, 0664);
	if (dup2(input1, STDIN_FILENO) == -1)
	{
		dprintf(2, "failed to dup2 \n");
		exit(0);
	}
	close(input1);
	free(file);
}

// it excludes the heredoc and its delemeter from the command
// check if its the last redi-in and prok heredoc and dup it to STDOUT
// ^^ call exec_redi_pipe_herdoc2
// if not the last heredoc it call for a fake heredoc

char	*exec_redi_pipe_herdoc(char *cmd, int i)
{
	char	*name;
	int		next_heredoc;

	name = redirection_name(ft_strdup(cmd + i + 2));
	next_heredoc = last_red_in(cmd, cmd + i);
	cmd = exlude_name(cmd, i, 2);
	if (next_heredoc)
		fake_herdoc(name);
	else if (!next_heredoc)
		exec_redi_pipe_herdoc2(name);
	free(name);
	return (cmd);
}

char	*exec_redi_loop_pip(char *cmd)
{
	int	i;

	i = 0;
	if (first_heredoc(cmd, 2) != -1)
		i = first_heredoc(cmd, 2);
	else
		i = first_redirection(cmd);
	if ((cmd[i] == '>' && cmd[i + 1] == '>') || cmd[i] == '>')
		cmd = exec_redi_pipe_output(cmd, i);
	if (cmd[i] == '<' && cmd[i + 1] == '<')
		cmd = exec_redi_pipe_herdoc(cmd, i);
	else if (cmd[i] == '<')
		cmd = exec_redi_pipe_input(cmd, i);
	return (cmd);
}
// while still a rediraction in the command it call for exec_redi_loop_pip
// to work on every redirection 

char	*exec_redirection_pipe(t_arg *command, char **buf,
			t_env **env_p, int *pipe_redi)
{
	char	*cmd;
	char	*file;

	(void)env_p;
	(void)pipe_redi;
	cmd = *buf;
	file = get_file_names();
	cmd = get_redi(command);
	while (first_redirection(cmd) != -1)
		cmd = exec_redi_loop_pip(cmd);
	free(cmd);
	cmd = join_list(command);
	free(*buf);
	*buf = cmd;
	return (file);
}

void	redirection(t_arg *command, char *buf, t_env **env_p)
{
	char	*file;
	int		pid;

	file = get_file_names();
	pid = fork();
	if (pid == -1)
	{
		printf("\033[0;31mUnable to create processe\n");
		return ;
	}
	else if (pid == 0)
	{
		buf = get_redi(command);
		while (first_redirection(buf) != -1)
			buf = exec_redi_loop_pip(buf);
		buf = join_list(command);
		execute_redirection(buf, env_p, file);
		exit(0);
	}
	sig_init();
	waitpid(pid, &(g_var.exit_status), 0);
	free(file);
	delete_arg(command);
	check_exit_status(pid);
}

int	redirect_output(char *name, unsigned int open_flag)
{
	int	file;

	file = open (name, O_RDWR | O_CREAT | open_flag, 0664);
	if (file == -1)
		exit (printf("llllIssue opening file1\n"));
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		exit (printf("Issue opening file2\n"));
	}
	close(file);
	return (0);
}

int	redirect_input(char *name)
{
	int	file;

	file = open (name, O_RDWR, 0664);
	if (file == -1)
	{
		ft_putstr_fd("Issue opening file3\n", 2);
		exit (1);
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Issue opening file4\n", 2);
		exit (1);
	}
	close(file);
	return (0);
}
