/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*map)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*cur;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew(map(lst->content));
	if (!new_list)
		return (NULL);
	cur = new_list;
	while (lst->next)
	{
		lst = lst->next;
		cur->next = ft_lstnew(map(lst->content));
		cur = cur->next;
		if (!cur)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
	}
	return (new_list);
}
