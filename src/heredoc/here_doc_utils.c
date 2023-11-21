/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:36:34 by rhorbach          #+#    #+#             */
/*   Updated: 2023/09/22 01:17:09 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include "pipe.h"

void	copy_char_to_res(char *result, int *result_index, char *str, int *i)
{
	result[*result_index] = str[*i];
	(*result_index)++;
	(*i)++;
}

void	set_int_to_zero(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

int	exit_code_count(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	random_digit(int fd)
{
	unsigned char	random_byte;

	if (read(fd, &random_byte, 1) != 1)
		return (1);
	return (random_byte % 10);
}

char	*generate_random_numbers(int length)
{
	int		i;
	int		fd;
	char	*numbers;
	char	*random_numbers;

	numbers = ft_strdup("0123456789");
	if (!numbers)
		return (NULL);
	random_numbers = malloc(sizeof(char) * (length + 1));
	if (!random_numbers)
		return (free(numbers), NULL);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (free(numbers), free(random_numbers), NULL);
	i = 0;
	while (i < length)
	{
		random_numbers[i] = numbers[random_digit(fd)];
		i++;
	}
	close(fd);
	random_numbers[length] = '\0';
	return (free(numbers), random_numbers);
}
