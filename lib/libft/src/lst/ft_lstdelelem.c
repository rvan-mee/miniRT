/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelelem.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:11:45 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/20 14:11:45 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdelelem(t_list **list, t_list *elem, void (*del)(void *))
{
	t_list	*cur;

	if (elem == *list)
	{
		*list = elem->next;
	}
	else
	{
		cur = *list;
		while (cur->next != elem)
			cur = cur->next;
		cur->next = elem->next;
	}
	ft_lstdelone(elem, del);
}
