/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: imisumi <imisumi@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:36:34 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/15 15:02:59 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <errno.h>
#include "pipe.h"
#include "types.h"
#include <bits/sigaction.h>

// Handles CTRL-\ (SIGQUIT)
static void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	set_exit_code(NOT_RECOVERABLE);
}

// Enables CTRL-\ (SIGQUIT)
void	enable_sigquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = sigquit_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

// Handles CTRL-C
// rl_set_prompt() to set arrow from green to red
//rl_set_prompt(prompt);
static void	sigint_handler(int signum)
{
	char	*prompt;

	(void)signum;
	set_exit_code(CONTROL_C_TERMINATED);
	prompt = get_prompt();
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free(prompt);
}

// Set up handler for CTRL-C
void	enable_sigint(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}
