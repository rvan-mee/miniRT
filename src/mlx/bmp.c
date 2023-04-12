/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/08 19:15:41 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/04/12 15:06:48 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <MLX42/MLX42.h>
#include <bmp.h>
#include <unistd.h>
#include <fcntl.h>

bool	write_file(int32_t fd, void *buf, size_t n_bytes);

static int32_t	write_bmp_header(int32_t fd, t_bmp bmp_data)
{
	static t_bmp_file_header	header;

	header.type = FILE_TYPE;
	header.size = bmp_data.data_size + HEADER_SIZE;
	header.file_pixel_offset = HEADER_SIZE;
	header.dib_header_size = DIB_HEADER_SIZE;
	header.width_pixels = bmp_data.width;
	header.height_pixels = bmp_data.height;
	header.color_planes = COLOR_PLANES_COUNT;
	header.bits_per_pixel = bmp_data.pixel_size * 8;
	header.image_size_bytes = bmp_data.data_size;
	return (write_file(fd, &header, sizeof(t_bmp_file_header)));
}

static int32_t	create_new_bmp_file(void)
{
	int32_t				fd;
	const char			*filename = "miniRT_portrait.bmp";

	fd = open(filename, O_RDWR | O_CREAT, 0664);
	if (fd == -1)
		perror("Error opening BMP file");
	return (fd);
}

static t_rgb	get_pixel_color(mlx_image_t *img, int32_t x, int32_t y)
{
	t_rgb	color;
	int8_t	*pixel_address;

	pixel_address = (int8_t *)&img->pixels[(y * img->width + x) \
						* sizeof(int32_t)];
	color.blue = *(pixel_address++);
	color.green = *(pixel_address++);
	color.red = *(pixel_address++);
	return (color);
}

static void	write_color_data(mlx_image_t *img, int32_t fd, t_bmp data)
{
	t_rgb	colors;
	int32_t	x;
	int32_t	y;
	size_t	i;

	i = 0;
	y = data.height;
	while (y > 0)
	{
		y--;
		x = 0;
		while (x < data.width)
		{
			colors = get_pixel_color(img, x, y);
			data.data[i++] = (unsigned char)colors.red;
			data.data[i++] = (unsigned char)colors.green;
			data.data[i++] = (unsigned char)colors.blue;
			x++;
		}
	}
	write_file(fd, data.data, data.data_size);
	free(data.data);
}

void	create_bmp(mlx_image_t *img)
{
	int32_t	fd;
	t_bmp	data;

	fd = create_new_bmp_file();
	if (fd == -1)
		return ;
	data.height = (int32_t) img->height;
	data.width = (int32_t) img->width;
	data.pixel_size = RGB;
	data.line_size = data.pixel_size * data.width;
	data.line_size += data.line_size % 4;
	data.data_size = data.line_size * data.height;
	data.data = ft_calloc(data.data_size, sizeof(unsigned char));
	if (!data.data || !write_bmp_header(fd, data))
	{
		if (!data.data)
			perror("Failed to allocate memory");
		free(data.data);
		close(fd);
		return ;
	}
	write_color_data(img, fd, data);
	close(fd);
}
