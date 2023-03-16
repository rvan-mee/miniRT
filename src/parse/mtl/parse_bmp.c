/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_bmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:00:20 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 18:22:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <unistd.h>

#define HEADER_SIZE 54

static bool	read_file(int32_t fd, void *buf, size_t n_bytes)
{
	ssize_t	readb;

	while (n_bytes != 0)
	{
		readb = read(fd, buf, n_bytes);
		if (readb <= 0)
			return (false);
		n_bytes -= readb;
		buf += readb;
	}
	return (true);
}

static bool	read_bmp(int32_t fd, t_bmp *bmp)
{
	t_bmp_file_header	bmp_head;

	if (!read_file(fd, &bmp_head, HEADER_SIZE))
		return (false);
	bmp->height = bmp_head.height_pixels;
	bmp->width = bmp_head.width_pixels;
	bmp->pixel_size = bmp_head.bits_per_pixel / 8;
	bmp->line_size = bmp->pixel_size * bmp->width;
	bmp->line_size += bmp->line_size % 4;
	bmp->data_size = bmp->height * bmp->line_size;
	bmp->data = malloc(bmp->data_size);
	if (!bmp->data)
		return (false);
	if (!read_file(fd, bmp->data, bmp_head.file_pixel_offset - HEADER_SIZE) || \
		!read_file(fd, bmp->data, bmp->data_size))
		return (free(bmp->data), false);
	return (true);
}

bool	parse_bmp(char *path, t_bmp *dst)
{
	int32_t	fd;

	if (!check_extension(path, ".bmp"))
		return (false);
	if (!open_file(path, &fd))
		return (false);
	if (!read_bmp(fd, dst))
		return (close(fd), false);
	close(fd);
	return (true);
}
