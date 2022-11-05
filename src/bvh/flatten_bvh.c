#include <bvh.h>
#include <stdlib.h>

static void	get_prim_costs(t_bvhbuilder *b, const uint32_t costs[])
{
	uint32_t	i;

	i = 0;
	while (i < b->length)
	{
		b->cost[i] = (float) costs[b->prims[i].type];
		b->surface_area[i] = sa(b->clusters[i].aabb);
		++i;
	}
}

static uint32_t	flatten(t_bvhbuilder *b, t_cluster *cluster, uint32_t i, t_nodeidx cur)
{
	const t_cluster	*cur_c = b->clusters + cur;
	const t_nodeidx	lr[2] = {cur_c->l, cur_c->r};

	if (cluster == cur_c)
	{
		cluster->prims = malloc(cluster->len * sizeof(t_objidx));
		if (cluster->prims == NULL)
			return (0);
	}
	if (lr[0] < b->length)
		cluster->prims[i++] = lr[0];
	if (lr[1] < b->length)
		cluster->prims[i++] = lr[1];
	if (lr[0] >= b->length)
		i = flatten(b, cluster, i, lr[0]);
	if (lr[1] >= b->length)
		i = flatten(b, cluster, i, lr[1]);
	return (i);
}

static void	prune_tree(t_bvhbuilder *b, const uint32_t aabb_cost)
{
	uint32_t	i;
	float		prim_cost;
	float		box_cost;
	t_cluster	*clus;

	i = b->length;
	while (i < b->node_idx)
	{
		clus = b->clusters + i;
		prim_cost = (float) (b->cost[clus->l] + b->cost[clus->r]);
		b->surface_area[i] = sa(clus->aabb);
		box_cost = 0;
		box_cost += b->surface_area[clus->l] / b->surface_area[i] * ((float) aabb_cost + b->cost[clus->l]);
		box_cost += b->surface_area[clus->r] / b->surface_area[i] * ((float) aabb_cost + b->cost[clus->r]);
		if (prim_cost < box_cost)
			clus->leaf = true;
		b->cost[i] = prim_cost;
		++i;
	}
}

static bool	flatten_td(t_bvhbuilder *b, t_nodeidx cur)
{
	t_cluster	*c;

	if (cur < b->length)
		return (true);
	c = b->clusters + cur;
	if (c->leaf)
		return (flatten(b, c, 0, cur));
	return (flatten_td(b, c->l) && flatten_td(b, c->r));
}

bool	flatten_bvh(t_bvhbuilder *b)
{
	const uint32_t	aabb_cost = 4;
	const uint32_t	costs[] = {
		[SPHERE] = 2,
		[PLANE] = 1,
		[CYLINDER] = 4,
	};

	get_prim_costs(b, costs);
	prune_tree(b, aabb_cost);
	return (flatten_td(b, b->node_idx - 1));
}
