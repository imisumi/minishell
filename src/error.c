/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:47:43 by rhorbach          #+#    #+#             */
/*   Updated: 2023/10/19 14:25:16 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

static t_error	*get_error_ptr(void)
{
	static t_error	err_ptr = OK;

	return (&err_ptr);
}

t_error	set_error(t_error err)
{
	t_error	*err_ptr;

	err_ptr = get_error_ptr();
	*err_ptr = err;
	return (*err_ptr);
}

t_error	get_error(void)
{
	t_error	*err_ptr;

	err_ptr = get_error_ptr();
	return (*err_ptr);
}

// void	print_error(t_error err)
// {
// 	static const char	*error_table[] = {
// 	[E_QUOTE] = "No closing quote found",
// 	[E_INVAL_PIPE] = "There is nothing to pipe to/from",
// 	[E_INVAL_REDIR] = "Missing redirect name",
// 	[E_AMBIGUOUS_REDIRECT] = "Ambiguous redirect"
// 	}; //TODO: Write error messages

// 	// ft_putendl_fd("Error", STDERR_FILENO);
// 	if (err == E_SYS)
// 		perror("minishell");
// 	else
// 	{
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		ft_putendl_fd((char *)error_table[err], STDERR_FILENO);
// 	}
// }

void	print_error(t_error err)
{
	static const char	*error_table[] = {
	[E_QUOTE] = "unexpected EOF while looking for matching",
	[E_INVAL_PIPE] = "syntax error",
	[E_INVAL_REDIR] = "syntax error",
	[E_AMBIGUOUS_REDIRECT] = "ambiguous redirect"
	};

	if (err == E_SYS)
		perror("minishell");
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd((char *)error_table[err], STDERR_FILENO);
	}
}
