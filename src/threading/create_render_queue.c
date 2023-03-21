/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_render_queue.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 13:37:49 by rvan-mee      #+#    #+#                 */
/*   Updated: 2023/03/21 19:21:48 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <thread.h>
#include <render.h>
#include <inttypes.h>

#define TOP		0
#define RIGHT	1
#define BOTTOM	2
#define LEFT	3
#define BLOCK_S	50

/**
 * Get the X and Y coordinates of an index in a spiral, O(1)
 *
 * The spiral will end up like:
 *
 * 	9	10	11	12							-1,-2	0,-2	1,-2	2,-2
 * 	8	1	2	13		with coords like:	-1,-1	0,-1	1,-1	2,-1
 * 	7	0	3	14							-1,0	0,0		1,0		2,0
 * 	6	5	4	15							-1,-1	0,-1	1,-1	2,-1
 * 	(and so on)
 *
 * Found in: https://stackoverflow.com/questions/398299/looping-in-a-spiral
 */
static t_ivec	spiral(size_t idx)
{
	int32_t	radius;
	int32_t	inner_points;
	int32_t	pos;
	int32_t	face;

	if (idx == 0)
		return ((t_ivec){0, 0, 0});
	--idx;
	radius = (int32_t)floorf((sqrtf((float) idx + 1) - 1) / 2) + 1;
	inner_points = (8 * radius * (radius - 1)) / 2;
	pos = (1 + (int32_t) idx - inner_points) % (radius * 8);
	face = pos / (radius * 2);
	if (face == TOP)
		return ((t_ivec){pos - radius, -radius, radius});
	else if (face == RIGHT)
		return ((t_ivec){radius, (pos % (radius * 2)) - radius, radius});
	else if (face == BOTTOM)
		return ((t_ivec){radius - (pos % (radius * 2)), radius, radius});
	else
		return ((t_ivec){-radius, radius - (pos % (radius * 2)), radius});
}

/**
 * Check if the spiral coordinates (pos) are valid (would fit in the screen).
 * If they are invalid, set the index to the next index that would be valid.
 *
 * The `extra' variable exists because skipping twice the radius is not always
 * enough (the radius would increase during the skip).
 */
static bool	check_oob(t_ivec pos, size_t *ip, t_civec limits[2], bool axis)
{
	int32_t		extra;
	int32_t		radius;

	radius = pos[2];
	if (pos[axis] < limits[axis][0])
	{
		extra = 0;
		if (axis == Y && -pos[X] >= radius)
			extra = 2;
		else if (axis == X && pos[Y] >= radius)
			extra = 1;
		*ip = *ip + ((radius + radius + limits[axis][0] - 1 + extra) * 2);
		return (true);
	}
	if (pos[axis] > limits[axis][1])
	{
		*ip = *ip + ((radius + radius - limits[axis][1]) * 2) - 1;
		return (true);
	}
	return (false);
}

/**
 * This used to be the body of the while loop in create_render_queue.
 *
 * If the index is a valid on-screen index in the spiral, create a new
 * render block and add it to the job list, after that increase the index.
 *
 * If the index is not valid, increase the index to the next valid one.
 *
 * returns false if an error occurred
 */
static
bool	add_next(t_threading *thr, size_t *i, t_civec sizes, t_civec limits[2])
{
	t_ivec		pos;
	t_render	block;

	pos = spiral(*i);
	if (check_oob(pos, i, limits, sizes[0] > sizes[1]))
		return (true);
	*i = *i + 1;
	block.start = (pos + sizes / 2);
	block.start[X] -= !(sizes[X] % 2);
	block.start *= BLOCK_S;
	block.size = (t_ivec){BLOCK_S, BLOCK_S};
	if (add_new_job_node(thr, start_render, block))
		return (true);
	clear_job_lst(thr);
	return (false);
}

/**
 * After adding all the spiral blocks that fit the screen completely, we still
 * need to fill in the edges. That's what this function does (duh)
 */
static bool	add_edges(t_threading *th, uint8_t side, t_civec screen_size)
{
	const t_ivec	mod = screen_size % BLOCK_S;
	t_ivec			size;
	t_ivec			pos;
	t_render		block;

	if (mod[side] == 0)
		return (true);
	size[side] = mod[side];
	size[!side] = (BLOCK_S * BLOCK_S) / size[side];
	pos[side] = screen_size[side] - mod[side];
	pos[!side] = 0;
	while (pos[!side] < screen_size[!side])
	{
		block.start = pos;
		block.size = size;
		if (block.size[!side] > screen_size[!side] - pos[!side])
			block.size[!side] = screen_size[!side] - pos[!side];
		if (!add_new_job_node(th, start_render, block))
			return (false);
		pos[!side] += (int32_t) block.size[!side];
	}
	return (true);
}

bool	create_render_queue(t_threading *thread, size_t w, size_t h)
{
	const t_ivec	sizes = {(int32_t) w / BLOCK_S, (int32_t) h / BLOCK_S};
	const t_ivec	limits[] = {\
		{-sizes[X] / 2 + !(sizes[X] % 2), sizes[X] / 2}, \
		{-sizes[Y] / 2, sizes[Y] / 2 - !(sizes[Y] % 2)},
	};
	size_t			size;
	size_t			i;

	size = sizes[sizes[0] < sizes[1]];
	size *= size;
	i = 0;
	while (i < size)
		if (!add_next(thread, &i, sizes, limits))
			return (false);
	if (add_edges(thread, X, (t_ivec){(int32_t) w, (int32_t) h}) && \
		add_edges(thread, Y, (t_ivec){(int32_t) w, (int32_t) h}))
		return (true);
	clear_job_lst(thread);
	return (false);
}
