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
void	intersect_node(t_cbvh *bvh, const uint32_t idx, t_hit *hit, t_queue *q)
{
	const t_cluster	*c = get_node(bvh, idx);
	const bool		is_p = is_prim(bvh, idx);
	float			distance;

	if (is_p)
		distance = intersect(bvh->prims + idx, &hit->ray, hit);
	else
		distance = aabb_intersect(c->aabb, &hit->ray);
	if (distance == MISS || distance < 0)
		return ;
	return (insert(q, node(idx, distance), is_p));
}

static inline
void	intersect_next(const t_bvh *bvh, t_hit *hit, t_queue *queue)
{
	t_prio	*cur;

	cur = queue->queue.next;
	queue->queue.next = cur->next;
	if (!get_node(bvh, cur->node)->leaf || is_prim(bvh, get_l(bvh, cur->node)))
		intersect_node(bvh, get_l(bvh, cur->node), hit, queue);
	else
		insert(queue, node(get_l(bvh, cur->node), cur->dist), false);
	if (!get_node(bvh, cur->node)->leaf || is_prim(bvh, get_r(bvh, cur->node)))
		intersect_node(bvh, get_r(bvh, cur->node), hit, queue);
	else
		insert(queue, node(get_r(bvh, cur->node), cur->dist), false);
	cur->next = queue->pool.next;
	queue->pool.next = cur;
}

bool	intersect_bvh(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	static __thread t_queue	queue;

	if (queue.pool.next == NULL)
		init_queue(&queue);
	hit->ray = *ray;
	intersect_node(bvh, bvh->root, hit, &queue);
	while (queue.queue.next != NULL && !is_prim(bvh, queue.queue.next->node))
		intersect_next(bvh, hit, &queue);
	if (queue.queue.next == NULL)
		return (false);
	hit->distance = queue.queue.next->dist;
	hit->object = bvh->prims + queue.queue.next->node;
	clear_queue(&queue);
	return (true);
}
