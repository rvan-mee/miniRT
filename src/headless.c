/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   headless.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 02:33:14 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/30 02:33:14 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <headless.h>
#include <minirt.h>
#include <thread.h>
#include <stdlib.h>
#include <bmp.h>

static bool	fake_mlx(t_minirt *data)
{
	t_fakeimg	*img;
	size_t		size;

	size = sizeof(t_fakeimg);
	size += data->width * data->height * sizeof(int32_t);
	img = malloc(size);
	if (!img)
		return (false);
	img->height = data->height;
	img->width = data->width;
	img->pixels = ((void *) img) + sizeof(t_fakeimg);
	data->img = (void *) img;
	return (true);
}

static int	cleanup(t_minirt *data, int status)
{
	if (data->img)
		free(data->img);
	return (status);
}

int	headless(t_minirt *data)
{
	if (!fake_mlx(data) || \
		!init_work_threads(data))
		return (cleanup(data, EXIT_FAILURE));
	wait_till_done(data->thread);
	quit_working(data->thread);
	create_bmp(data->img);
	join_threads(data);
	return (cleanup(data, EXIT_SUCCESS));
}
