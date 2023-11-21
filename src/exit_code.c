/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:47:43 by rhorbach          #+#    #+#             */
/*   Updated: 2023/08/29 17:31:37 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "types.h"

static t_exit_code	*get_exit_code_ptr(void)
{
	static t_exit_code	exit_code = SUCCESS;

	return (&exit_code);
}

void	set_exit_code(t_exit_code err)
{
	t_exit_code	*exit_code;

	exit_code = get_exit_code_ptr();
	*exit_code = err;
}

t_exit_code	get_exit_code(void)
{
	t_exit_code	*exit_code;

	exit_code = get_exit_code_ptr();
	return (*exit_code);
}
