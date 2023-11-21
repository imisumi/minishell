/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:36:34 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/23 16:08:36 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

// Handles CTRL-C in pipe
static void	sigint_handler_pipe(int signum)
{
	(void)signum;
	set_exit_code(CONTROL_C_TERMINATED);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// Set up handler for CTRL-C
void	enable_sigint_pipe(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = sigint_handler_pipe;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

// Disables CTRL-\ (SIGQUIT)
void	disable_sigquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

// Handles CTRL-C in pipe
static void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	set_exit_code(CONTROL_C_TERMINATED);
	ft_putstr_fd("\n", STDERR_FILENO);
	storage(1, SET);
}

// Set up handler for CTRL-C
void	enable_sigint_heredoc(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = sigint_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}
