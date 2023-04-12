/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 12:58:22 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/20 12:58:22 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <unistd.h>
#include <dynarr.h>
#include <libft.h>

static t_gnl_err	add_til_newline(t_filebuf *buf, t_dynarr *linebuf)
{
	const char	*bufstart = buf->buf + buf->start;
	const char	*nl = ft_memchr(bufstart, '\n', buf->len);
	size_t		len;

	if (nl == NULL)
		len = buf->len;
	else
		len = nl - bufstart + 1;
	if (!dynarr_add(linebuf, bufstart, len))
		return (GNL_ERROR);
	buf->len -= len;
	buf->start += len;
	if (buf->len == 0)
		buf->start = 0;
	if (nl != NULL)
		return (GNL_DONE);
	else
		return (GNL_CONTINUE);
}

/**
 * Checks if leftover contains a newline. If not, read BUFFER_SIZE bytes
 * and append them onto leftover. Repeat.
 *
 * Returns NULL if anything went wrong
 */
static
t_gnl_err	read_until_newline(int fd, t_filebuf *buf, t_dynarr *linebuf)
{
	ssize_t	read_bytes;
	int		result;

	while (true)
	{
		if (buf->len != 0)
		{
			result = add_til_newline(buf, linebuf);
			if (result != GNL_CONTINUE)
				return (result);
		}
		read_bytes = read(fd, buf->buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (GNL_ERROR_FILE);
		if (read_bytes == 0)
			return (GNL_FINISHED);
		buf->len = read_bytes;
	}
}

bool	init_gnl(int fd, t_list **list, t_list **dst, t_dynarr *buf);
size_t	clean_gnl(t_dynarr *linebuf, t_list **list, t_list *cur, int status);

size_t	get_next_line(int fd, char **dst)
{
	static t_list	*list = NULL;
	t_list			*cur;
	t_gnl_err		result;
	t_dynarr		linebuf;

	if (!init_gnl(fd, &list, &cur, &linebuf))
		return (SIZE_MAX);
	result = read_until_newline(fd, cur->content, &linebuf);
	if ((result != GNL_DONE && result != GNL_FINISHED) || \
		!dynarr_addone(&linebuf, "\0") || \
		!dynarr_finalize(&linebuf))
		return (clean_gnl(&linebuf, &list, cur, result));
	if (result == GNL_FINISHED)
		ft_lstdelelem(&list, cur, NULL);
	if (linebuf.length == 1)
		dynarr_delete(&linebuf);
	else
		*dst = linebuf.arr;
	return (linebuf.length - 1);
}

char	*get_next_line_dumb(int fd)
{
	char	*line;
	size_t	len;

	len = get_next_line(fd, &line);
	if (len == SIZE_MAX || len == 0)
		return (NULL);
	return (line);
}
