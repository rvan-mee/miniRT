#include <bvh.h>
#include <libft.h>
#include <render.h>
#include <stdio.h>

static void	link_nodes(t_prio *nodes, t_prio nodebuf[64])
{
	uint16_t	i;
	t_prio	*cur;

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
	float		distance;
	static uint64_t	intersects[2];

	if (idx == UINT32_MAX)
		return (void) dprintf(1, "%llu prim intersections, %llu aabb intersections\n", intersects[0], intersects[1]);
	const bool	is_prim = idx < bvh->prim_size;
	if (is_prim)
		distance = intersect(bvh->prims + idx, ray);
	else
		distance = aabb_intersect(bvh->clusters[idx].aabb, ray);
	++intersects[is_prim];
	if (distance == MISS || distance < 0)
		return ;
	insert(idx, distance, queue, nodes, is_prim);
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
		cur->next = nodes.next;
		nodes.next = cur;
		intersect_node(bvh, bvh->clusters[cur->cluster].l, ray, &queue, &nodes);
		intersect_node(bvh, bvh->clusters[cur->cluster].r, ray, &queue, &nodes);
	}
	if (queue.next == NULL)
		return (false);
	hit->distance = queue.next->dist;
	hit->object = bvh->prims + queue.next->cluster;
	return (true);
}

void	print_shits(void)
{
	intersect_node(NULL, UINT32_MAX, NULL, NULL, NULL);
}
