/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 17:02:54 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/09/06 17:16:14 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "types.h"

t_env	*get_env_var(t_list *env_lst, char *name);
t_env	*get_env_var_n(t_list *env_lst, char *name, size_t n);

t_error	init_env_lst(t_data *data, char **envp);

t_error	set_env_var(t_list **env_lst, char *name, char *value);
t_error	set_env_var_composite(t_list **env_lst, char *env);
void	unset_env_var(t_list **env_lst, char *name);

#endif
