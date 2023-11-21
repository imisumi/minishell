/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:11:45 by rhorbach          #+#    #+#             */
/*   Updated: 2023/11/21 16:23:08 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "types.h"
#include "pipe.h"
#include "error.h"
#include "tokens.h"
#include "cmd_lst.h"
#include "redir_lst.h"
#include <readline/readline.h>
#include <readline/history.h>

//TODO: maybe incorporate pipex, cuz issue when all whitespace
t_error	parse_input(t_data *data, char *input)
{
	t_list	*tokens;

	tokens = NULL;
	if (tokenize(&tokens, input) != OK)
	{
		ft_lstclear(&tokens, &free_token);
		return (get_error());
	}
	if (all_whitepace(tokens))
	{
		ft_lstclear(&tokens, &free_token);
		return (OK);
	}
	if (complete_tokens(&tokens, data->env_lst) != OK \
		|| cmd_parser(data, tokens) != OK)
	{
		ft_lstclear(&tokens, &free_token);
		return (get_error());
	}
	ft_lstclear(&tokens, &free_token);
	return (OK);
}

t_error	handle_input(t_data *data, char *input)
{
	if (input[0] != '\0')
	{
		if (parse_input(data, input) != OK)
		{
			free(input);
			print_error(get_error());
			set_exit_code(2);
			if (get_error() == E_AMBIGUOUS_REDIRECT)
				set_exit_code(1);
		}
		else
		{
			free(input);
			if (pipex(data) != OK)
				return (get_error());
			free_cmd_lst(data->cmd_list);
		}
	}
	return (OK);
}

// t_error	minishell(char **envp)
// {
// 	static t_data	data;
// 	char			*input;
// 	char			*prompt;

// 	data.utils = init_utils();
// 	enable_sigint();
// 	set_exit_code(SUCCESS);
// 	if (init_env_lst(&data, envp) != OK && set_old_pwd(&data) != OK)
// 		return (get_error());
// 	while (true)
// 	{
// 		fill_env_file(data);
// 		disable_sigquit();
// 		prompt = get_prompt();
// 	#if NO_READLINE
// 		printf("%s", prompt);
// 		fflush(NULL);
// 		if (get_next_line(STDIN_FILENO, &input) == GNL_EOF)
// 		{
// 			printf("EOF\n");
// 			// free(input);
// 			free(prompt);
// 			free_data(&data);
// 			// free_cmd_lst(data.cmd_list);
// 			return (OK);
// 		}
// 		if (input[0] == '\n')
// 		{
// 			free(prompt);
// 			free(input);
// 			printf("enter\n");
// 			continue;
// 		}
// 	#else
// 		input = readline(prompt);
// 		if (input == NULL)
// 		{
// 			printf("EOF\n");
// 			//TODO free data (free_data segfaults)
// 			// free_data(&data);
// 			// free
// 			free_eof(&data);
// 			free(prompt);
// 			rl_clear_history();
// 			return (OK);
// 		}
// 		if (input[0] == '\0')
// 		{
// 			printf("enter\n");
// 			free(input);
// 			free(prompt);
// 			continue;
// 		}
// 	#endif
// 		free(prompt);
// 		if (is_only_whitespace(input) == false)
// 		{
// 			#if !NO_READLINE
// 				add_history(input);
// 			#endif
// 			enable_sigquit();
// 			if (handle_input(&data, input) != OK)
// 			{
// 				// free_data(&data);
// 				// free_cmd_lst(data.cmd_list);
// 				free_data_cmd(&data);
// 				return (get_error());
// 			}
// 		}
// 	}
// 	#if !NO_READLINE
// 		rl_clear_history();
// 	#endif
// 	return (OK);
// }

static t_error	check_input(t_data *data, char *prompt, char *input)
{
	if (input[0] == '\0')
	{
		free(input);
		free(prompt);
	}
	else
	{
		free(prompt);
		if (is_only_whitespace(input) == false)
		{
			add_history(input);
			enable_sigquit();
			if (handle_input(data, input) != OK)
			{
				free_data_cmd(data);
				return (get_error());
			}
		}
	}
	return (OK);
}

void	print_open_fd()
{
	for (int fd = 0; fd < 1024; fd++) { // You can adjust the upper limit as needed
        int flags = fcntl(fd, F_GETFD);
        if (flags == -1) {
            // An error occurred, so fd might not be open
            continue;
        }
        if (flags & FD_CLOEXEC) {
            // FD_CLOEXEC flag is set, indicating that fd is marked for automatic
            // close on exec, so it's not open in your minishell
            continue;
        }
        // If the code reaches here, fd is open and not marked for automatic close
        printf("File descriptor %d is open.\n", fd);
    }
}

t_error	minishell(char **envp)
{
	static t_data	data;
	char			*input;
	char			*prompt;

	data.utils = init_utils();
	enable_sigint();
	if (init_env_lst(&data, envp) != OK && set_old_pwd(&data) != OK)
		return (get_error());
	while (true)
	{
		disable_sigquit();
		prompt = get_prompt();
		input = readline(prompt);
		if (input == NULL)
			return (clean_input(&data, prompt));
		if (check_input(&data, prompt, input) != OK)
			return (get_error());
		// print_open_fd();
	}
	return (OK);
}



int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	if (minishell(envp) != OK)
	{
		rl_clear_history();
		print_error(get_error());
		return (EXIT_FAILURE);
	}
	rl_clear_history();
	// print_open_fd();
	return (get_exit_code());
}
