/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_bmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:00:20 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/16 14:35:23 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>
#include <parse.h>
#include <libft.h>
#include <unistd.h>
#include <bmp.h>

#define HEADER_SIZE 54

static bool	read_bmp(int32_t fd, char *path, t_bmp *bmp)
{
	t_bmp_file_header	bmp_head;
	int32_t				read_ret;
	int32_t 			i;

	read_ret = read(fd, &bmp_head, HEADER_SIZE);
	if (read_ret == -1 || read_ret != HEADER_SIZE)
		return (false);
	bmp->height = bmp_head.height_pixels;
	bmp->width = bmp_head.width_pixels;
	bmp->arr_len = 3 * bmp->width * abs(bmp->height);
	bmp->data = malloc (sizeof(unsigned char) * bmp->arr_len + 1);
	read_ret = read(fd, bmp->data, bmp->arr_len);
	if (read_ret == -1 || read_ret != bmp->arr_len)
		return (false);
	bmp->data[bmp->arr_len] = '\0';
    return (true);
}

t_bmp	*parse_bmp(t_parse_data *data, char *path)
{
	t_bmp	*bmp;
	int32_t	fd;

	if (!check_extension(path, ".bmp"))
		return (NULL);
	if (!open_file(path, &fd))
		return (NULL);
	bmp = malloc(sizeof(t_bmp));
	if (!bmp)
		return (close(fd), NULL);
	bmp->name = ft_strdup(path);
	if (!read_bmp(fd, path, bmp))
		return (close(fd), NULL);
	close(fd);
	return (bmp);
}


