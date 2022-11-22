/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_bvh.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 16:27:02 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/22 15:54:50 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>
#include <libft.h>
#include <render.h>

// Queue
#define Q	0
// Pool
#define P	1

static void	link_nodes(t_prio *nodes, t_prio nodebuf[512])
{
	uint16_t	i;
	t_prio		*cur;

	i = 0;
	cur = nodes;
	while (i < 512)
	{
		cur->next = nodebuf + i;
		cur = cur->next;
		++i;
	}
	cur->next = NULL;
}

static void	insert(
		const uint32_t idx,
		const float distance,
		const bool is_prim,
		t_prio nodes[2])
{
	t_prio	*insert_after;
	t_prio	*node;
	t_prio	*next;

	if (nodes[P].next == NULL)
	{
		printf("exit in insert\n");
		exit(-1);
	}
	insert_after = nodes + Q;
	while (insert_after->next != NULL && insert_after->next->dist < distance)
		insert_after = insert_after->next;
	node = nodes[P].next;
	nodes[P].next = node->next;
	*node = (t_prio){idx, distance, insert_after->next};
	insert_after->next = node;
	if (!is_prim)
		return ;
	next = node->next;
	node->next = NULL;
	while (next)
	{
		node = next;
		next = node->next;
		node->next = nodes[P].next;
		nodes[P].next = node;
	}
}

static void	intersect_node(
		const t_bvh *bvh,
		const uint32_t idx,
		const t_ray *ray,
		t_prio nodes[2])
{
	const t_cluster	*c = get_node(bvh, idx);
	const bool		is_p = is_prim(bvh, idx);
	float			distance;
	t_hit			hit;

	if (is_p)
		distance = intersect(bvh->prims + idx, ray, &hit);
	else
		distance = aabb_intersect(c->aabb, ray);
	if (distance == MISS || distance < 0)
		return ;
	return (insert(idx, distance, is_p, nodes));
}

static inline void	intersect_next(
		const t_bvh *bvh,
		const t_ray *ray,
		t_prio nodes[2])
{
	t_prio	*cur;

	cur = nodes[Q].next;
	nodes[Q].next = cur->next;
	if (!get_node(bvh, cur->node)->leaf || is_prim(bvh, get_l(bvh, cur->node)))
		intersect_node(bvh, get_l(bvh, cur->node), ray, nodes);
	else
		insert(get_l(bvh, cur->node), cur->dist, false, nodes);
	if (!get_node(bvh, cur->node)->leaf || is_prim(bvh, get_r(bvh, cur->node)))
		intersect_node(bvh, get_r(bvh, cur->node), ray, nodes);
	else
		insert(get_r(bvh, cur->node), cur->dist, false, nodes);
	cur->next = nodes[P].next;
	nodes[P].next = cur;
}

bool	intersect_bvh(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	t_prio	nodes[2];
	t_prio	nodebuf[512];

	link_nodes(nodes + P, nodebuf);
	nodes[Q].next = NULL;
	intersect_node(bvh, bvh->root, ray, nodes);
	while (nodes[Q].next != NULL && !is_prim(bvh, nodes[Q].next->node))
		intersect_next(bvh, ray, nodes);
	if (nodes[Q].next == NULL)
		return (false);
	hit->distance = nodes[Q].next->dist;
	hit->object = bvh->prims + nodes[Q].next->node;
	return (true);
}
