/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 15:32:40 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/09/19 17:01:07 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_lst_dispose_one(t_list **lst, void (*del)(void *));
void	**ft_lst_to_array_rev(t_list *lst);
void	**ft_lst_to_array(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void	*));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew_back(t_list **lst, void *content);
t_list	*ft_lstnew_front(t_list **lst, void *content);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

#endif
