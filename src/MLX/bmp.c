/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/08 19:15:41 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 15:02:27 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <miniRT.h>
#include <mlx.h>
#include <bmp.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

static int32_t	write_bmp_header(int32_t fd, t_bmp_data bmp_data)
{
	static t_bmp_file_header	header;

	header.type = FILE_TYPE;
	header.size = (HEIGHT * WIDTH * sizeof(int32_t)) + HEADER_SIZE;
	header.header_offset = HEADER_SIZE;
	header.dib_header_size = DIB_HEADER_SIZE;
	header.width_pixels = WIDTH;
	header.height_pixels = HEIGHT;
	header.color_planes = COLOR_PLANES_COUNT;
	header.bits_per_pixel = BITS_PER_PIXEL;
	header.image_size_bytes = bmp_data.data_size;
	if (write(fd, &header, sizeof(t_bmp_file_header)) == -1)
	{
		write(STDERR_FILENO, "Writing to BMP file failed\n", 28);
		return (-1);
	}
	return (0);
}

static int32_t	create_new_bmp_file(void)
{
	int32_t				fd;
	const char			*filename = "miniRT_portrait.bmp";

	fd = open(filename, O_RDWR | O_CREAT, 0664);
	if (fd == -1)
		write(STDERR_FILENO, "Error opening BMP file\n", 24);
	return (fd);
}

static t_rgb	get_pixel_color(mlx_image_t *img, int32_t x, int32_t y)
{
	t_rgb	color;
	int8_t	*pixel_address;

	pixel_address = (int8_t *)&img->pixels[(y * WIDTH + x) \
						* sizeof(int32_t)];
	color.blue = *(pixel_address++);
	color.green = *(pixel_address++);
	color.red = *(pixel_address++);
	return (color);
}

static void	write_color_data(mlx_image_t *img, int32_t fd, t_bmp_data data)
{
	t_rgb			colors;
	uint32_t		x;
	uint32_t		y;
	size_t			i;

	i = 0;
	y = HEIGHT - 1;
	while (1)
	{
		x = 0;
		while (x < WIDTH)
		{
			colors = get_pixel_color(img, x, y);
			data.data[i++] = (unsigned char)colors.red;
			data.data[i++] = (unsigned char)colors.green;
			data.data[i++] = (unsigned char)colors.blue;
			x++;
		}
		if (y == 0)
			break ;
		y--;
	}
	if (write(fd, data.data, data.data_size) == -1)
		write(STDERR_FILENO, "Writing to BMP file failed\n", 28);
	free(data.data);
}

void	create_bmp(mlx_image_t *img)
{
	int32_t		fd;
	t_bmp_data	data;

	fd = create_new_bmp_file();
	if (fd == -1)
		return ;
	data.padding = WIDTH % sizeof(int32_t);
	data.line_size = RGB * WIDTH + data.padding;
	data.data_size = data.line_size * HEIGHT;
	data.data = ft_calloc(data.data_size, sizeof(unsigned char));
	if (!data.data || write_bmp_header(fd, data) == -1)
	{
		if (!data.data)
			write(STDERR_FILENO, "Failed to allocate memory\n", 27);
		close(fd);
		exit(EXIT_FAILURE);
	}
	write_color_data(img, fd, data);
	close(fd);
}
