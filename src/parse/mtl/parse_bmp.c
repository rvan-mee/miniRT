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

#include <texture.h>
#include <parse.h>
#include <libft.h>
#include <unistd.h>
#include <bmp.h>

#define HEADER_SIZE 54

static bool	read_bmp(int32_t fd, t_bmp *bmp)
{
	t_bmp_file_header	bmp_head;
	int32_t				arr_len;
	int32_t				read_ret;

	read_ret = read(fd, &bmp_head, HEADER_SIZE);
	if (read_ret == -1 || read_ret != HEADER_SIZE)
		return (false);
	bmp->height = bmp_head.height_pixels;
	bmp->width = bmp_head.width_pixels;
	bmp->padding = bmp_head.width_pixels % sizeof(int32_t);
	arr_len = 3 * bmp->width * bmp->height;
	bmp->data = malloc (sizeof(unsigned char) * arr_len);
	if (!bmp->data)
		return (false);
	read_ret = read(fd, bmp->data, arr_len);
	if (read_ret == -1 || read_ret != arr_len)
		return (free(bmp->data), false);
	return (true);
}

bool	parse_bmp(char *path, t_bmp *dst)
{
	int32_t	fd;

	dst->name = path;
	if (!check_extension(path, ".bmp"))
		return (false);
	if (!open_file(path, &fd))
		return (false);
	if (!read_bmp(fd, dst))
		return (close(fd), false);
	close(fd);
	return (true);
}
