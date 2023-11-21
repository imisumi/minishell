/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 16:34:33 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/08/03 14:32:53 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks whether the arg is alphanumeric
 * @param arg Char to be evaluated
 * @returns 1 if character was alphanumeric, 0 if not
 */
int	ft_isalnum(int arg)
{
	return (ft_isalpha(arg) || ft_isdigit(arg));
}
