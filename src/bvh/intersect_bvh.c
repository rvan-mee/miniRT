/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_bvh.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 16:27:02 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/06 16:27:02 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>
#include <libft.h>
#include <render.h>

static void	link_nodes(t_prio *nodes, t_prio nodebuf[64])
{
	uint16_t	i;
	t_prio		*cur;

	i = 0;
	cur = nodes;
	while (i < 64)
	{
		cur->next = nodebuf + i;
		cur = cur->next;
		++i;
	}
	cur->next = NULL;
}

static void	clear_queue(t_prio *node, t_prio *nodes)
{
	t_prio	*next;

	next = node->next;
	node->next = NULL;
	node = next;
	while (node)
	{
		next = node->next;
		node->next = nodes->next;
		nodes->next = node;
		node = next;
	}
}

static void	insert(uint32_t idx, float distance, t_prio *queue, t_prio *nodes, const bool is_prim)
{
	t_prio	*insert_after;
	t_prio	*node;

	if (nodes->next == NULL)
		exit(-1);
	insert_after = queue;
	while (insert_after->next != NULL && insert_after->next->dist < distance)
		insert_after = insert_after->next;
	node = nodes->next;
	nodes->next = node->next;
	node->next = insert_after->next;
	insert_after->next = node;
	node->dist = distance;
	node->cluster = idx;
	if (is_prim)
		clear_queue(node, nodes);
}

static void	intersect_node(t_bvh *bvh, uint32_t idx, t_ray *ray, t_prio *queue, t_prio *nodes)
{
	const t_cluster	*c = get_clust(bvh, idx);
	float			distance;

	if (is_prim(bvh, idx))
		distance = intersect(bvh->prims + idx, ray);
	else
		distance = aabb_intersect(c->aabb, ray);
	if (distance == MISS || distance < 0)
		return ;
	return (insert(idx, distance, queue, nodes, is_prim(bvh, idx)));
}

bool	intersect_bvh(t_bvh *bvh, t_ray *ray, t_hit *hit)
{
	t_prio	queue;
	t_prio	nodes;
	t_prio	nodebuf[64];
	t_prio	*cur;

	link_nodes(&nodes, nodebuf);
	queue.next = NULL;
	intersect_node(bvh, bvh->root, ray, &queue, &nodes);
	while (queue.next != NULL && queue.next->cluster >= bvh->prim_size)
	{
		cur = queue.next;
		queue.next = cur->next;
		if (!get_clust(bvh, cur->cluster)->leaf || is_prim(bvh, get_l(bvh, cur->cluster)))
			intersect_node(bvh, get_clust(bvh, cur->cluster)->l, ray, &queue, &nodes);
		else
			insert(get_l(bvh, cur->cluster), cur->dist, &queue, &nodes, false);
		if (!get_clust(bvh, cur->cluster)->leaf || is_prim(bvh, get_r(bvh, cur->cluster)))
			intersect_node(bvh, get_r(bvh, cur->cluster), ray, &queue, &nodes);
		else
			insert(get_r(bvh, cur->cluster), cur->dist, &queue, &nodes, false);
		cur->next = nodes.next;
		nodes.next = cur;
	}
	if (queue.next == NULL)
		return (false);
	hit->distance = queue.next->dist;
	hit->object = bvh->prims + queue.next->cluster;
	return (true);
}
