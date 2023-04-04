/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_bvh.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 16:27:02 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/28 15:19:03 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

static t_prio	node(const uint32_t idx, const float dist)
{
	return ((t_prio){\
		.node = idx,
		.dist = dist,
	});
}

static
float	intersect_node(t_cbvh *bvh, t_nodeidx idx, t_hit *hit, t_fvec inv_dir)
{
	const t_cluster	*c = get_node(bvh, idx);
	const bool		is_p = is_prim(bvh, idx);

	if (is_p)
		return (intersect(bvh->prims + idx, &hit->ray, hit));
	else
		return (aabb_intersect(c->aabb, &hit->ray, inv_dir));
}

// This function is a little less readable because of norminette
// an extra param was needed for the inverse direction, so I couldn't insert
// in the function above
static inline
void	intersect_next(t_cbvh *bvh, t_hit *hit, t_queue *queue, t_fvec inv_dir)
{
	t_prio		*cur;
	t_nodeidx	child;
	float		dist;

	cur = queue->queue.next;
	queue->queue.next = cur->next;
	child = get_l(bvh, cur->node);
	dist = intersect_node(bvh, child, hit, inv_dir);
	if (dist >= 0 && dist != INFINITY)
		insert(queue, node(child, dist), is_prim(bvh, child));
	child = get_r(bvh, cur->node);
	dist = intersect_node(bvh, child, hit, inv_dir);
	if (dist >= 0 && dist != INFINITY)
		insert(queue, node(child, dist), is_prim(bvh, child));
	cur->next = queue->pool.next;
	queue->pool.next = cur;
}

bool	intersect_bvh(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	static __thread t_queue	queue;
	t_fvec					inv_dir;

	if (queue.pool.next == NULL)
		init_queue(&queue);
	hit->ray = *ray;
	inv_dir = 1.0f / ray->direction;
	insert(&queue, node(bvh->root, 0.0f), false);
	while (queue.queue.next != NULL && !is_prim(bvh, queue.queue.next->node))
		intersect_next(bvh, hit, &queue, inv_dir);
	if (queue.queue.next == NULL)
		return (false);
	hit->distance = queue.queue.next->dist;
	hit->object = bvh->prims + queue.queue.next->node;
	clear_queue(&queue);
	return (true);
}
