/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 22:49:54 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/22 22:49:54 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <libft.h>
#include <dynarr.h>

static t_list	*find_list(t_list **list, int fd)
{
	t_list		*cur;
	t_filebuf	*content;

	cur = *list;
	while (cur)
	{
		content = cur->content;
		if (content->fd == fd)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

static t_list	*create_list(t_list **list, int fd)
{
	t_list		*cur;
	t_filebuf	*content;

	cur = malloc(sizeof(t_list) + sizeof(t_filebuf));
	if (!cur)
		return (NULL);
	cur->content = cur + 1;
	content = cur->content;
	*content = (t_filebuf){fd, {}, 0, 0};
	ft_lstadd_front(list, cur);
	return (cur);
}

static t_list	*find_or_create_list(t_list **list, int fd)
{
	t_list		*cur;

	cur = find_list(list, fd);
	if (!cur)
		cur = create_list(list, fd);
	return (cur);
}

bool	init_gnl(int fd, t_list **list, t_list **dst, t_dynarr *buf)
{
	if (fd >= 0)
	{
		*dst = find_or_create_list(list, fd);
		if (*dst && dynarr_create(buf, 128, sizeof(char)))
			return (true);
	}
	ft_lstclear(list, NULL);
	return (false);
}

size_t	clean_gnl(t_dynarr *linebuf, t_list **list, t_list *cur, int status)
{
	dynarr_delete(linebuf);
	if (status == GNL_ERROR_FILE)
		ft_lstdelelem(list, cur, NULL);
	else
		ft_lstclear(list, NULL);
	return (SIZE_MAX);
}
