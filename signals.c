/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 19:45:38 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/19 01:55:24 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_init(void)
{
	signal(SIGINT, sighandle);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
