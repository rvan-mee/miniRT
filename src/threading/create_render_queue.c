/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_render_queue.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 13:37:49 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/26 21:46:59 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <render.h>
#include <libft.h>

#define DIFF 1

static t_render	*new_render_block(t_minirt *data, size_t start[2], size_t end[2])
{
	t_render	*render_block;

	render_block = malloc(sizeof(t_render));
	if (!render_block)
		return (NULL);
	render_block->start_pixels[X] = start[X];
	render_block->start_pixels[Y] = start[Y];
	render_block->end_pixels[X] = end[X];
	render_block->end_pixels[Y] = end[Y];
	render_block->size[X] = end[X] - start[X];
	render_block->size[Y] = end[Y] - start[Y];
	render_block->camera.coords = data->scene.camera.coords;
	render_block->camera.camera.fov = data->scene.camera.camera.fov;
	render_block->camera.camera.orientation = data->scene.camera.camera.orientation;
	return (render_block);
}

static void	set_offset(t_minirt *data, size_t offset[3])
{
	const size_t	width = data->width;
	const size_t	height = data->height;

	if (height < width)
		offset[0] = height / BLOCK_C;
	else
		offset[0] = width / BLOCK_C;
	offset[X + DIFF] = width % offset[0];
	offset[Y + DIFF] = height % offset[0];
}

// function for norm :/
static void	increment(size_t *start, size_t *end, size_t *offset, int coord)
{
	if (coord == X)
	{
		start[X] = end[X];
		end[X] += offset[0];
		return ;
	}
	start[Y] = end[Y];
	end[Y] += offset[0];
}

// is it faster to go >>> down <<< down >>>
// or >>> down reset left >>> down reset left >>>
bool	create_render_queue(t_minirt *data)
{
	size_t		offset[3];
	size_t		start[2];
	size_t		end[2];
	t_render	*new_block;

	set_offset(data, offset);
	start[Y] = 0;
	end[Y] = offset[0];
	while (end[Y] <= data->height)
	{
		start[X] = 0;
		end[X] = offset[0];
		if (end[Y] + offset[0] > data->height)
			end[Y] += offset[Y + DIFF];
		while (end[X] <= data->width)
		{
			if (end[X] + offset[0] > data->width)
				end[X] += offset[X + DIFF];
			new_block = new_render_block(data, start, end);
			if (!new_block
				|| !add_new_job_node(data, start_render, new_block))
				return (clear_job_lst(data), free(new_block), false);
			increment(start, end, offset, X);
		}
		increment(start, end, offset, Y);
	}
	return (true);
}
