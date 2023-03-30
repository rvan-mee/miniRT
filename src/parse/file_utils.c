/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 00:28:30 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/22 00:28:30 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <parse.h>
#include <get_next_line.h>

#define ERR_OPEN	"Error\nFile failed to open: %s: %s\n"
#define ERR_READ	"Error\nReading from fd %d failed: %s\n"
#define ERR_WRITE	"Error\nWriting to fd %d failed: %s\n"

bool	open_file(const char *path, int32_t *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd != -1)
		return (true);
	dprintf(STDERR_FILENO, ERR_OPEN, path, strerror(errno));
	return (false);
}

bool	read_file(int32_t fd, void *buf, size_t n_bytes)
{
	ssize_t	readb;

	while (n_bytes != 0)
	{
		readb = read(fd, buf, n_bytes);
		if (readb <= 0)
		{
			dprintf(STDERR_FILENO, ERR_READ, fd, strerror(errno));
			return (false);
		}
		n_bytes -= readb;
		buf += readb;
	}
	return (true);
}

bool	write_file(int32_t fd, void *buf, size_t n_bytes)
{
	ssize_t	wroteb;

	while (n_bytes != 0)
	{
		wroteb = write(fd, buf, n_bytes);
		if (wroteb <= 0)
		{
			dprintf(STDERR_FILENO, ERR_WRITE, fd, strerror(errno));
			return (false);
		}
		n_bytes -= wroteb;
		buf += wroteb;
	}
	return (true);
}

t_parse_err	get_line(t_conf_data *data, char **dst)
{
	size_t	len;

	len = get_next_line(data->fd, dst);
	if (len == 0)
		return (SUCCESS);
	if (len == SIZE_MAX)
		return (ALLOC);
	data->curr_line++;
	return (CONTINUE);
}
