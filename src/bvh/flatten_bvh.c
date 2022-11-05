#include <bvh.h>
#include <stdio.h>
#include <ft_math.h>

static inline float	sa(t_aabb aabb)
{
	const t_fvec	size = aabb.max - aabb.min;

	return (dot_product(size, size));
}

static void	get_prim_costs(t_bvhbuilder *b, const uint32_t costs[])
{
	uint32_t	i;

	i = 0;
	while (i < b->length)
	{
		b->cost[i] = costs[b->prims[i].type];
		b->surface_area[i] = sa(b->clusters[i].aabb);
		++i;
	}
}

static void	prune_tree(t_bvhbuilder *b, const uint32_t aabb_cost)
{
	uint32_t	i;
	uint32_t	prim_cost;
	uint32_t	box_cost;
	t_cluster	*clus;

	i = b->length;
	while (i < b->node_idx)
	{
		clus = b->clusters + i;
		prim_cost = b->cost[clus->l] + b->cost[clus->r];
		b->surface_area[i] = sa(clus->aabb);
		box_cost = 0;
		box_cost += b->surface_area[clus->l] / b->surface_area[i] * (aabb_cost + b->cost[clus->l]);
		box_cost += b->surface_area[clus->r] / b->surface_area[i] * (aabb_cost + b->cost[clus->r]);
		if (prim_cost < box_cost)
			clus->leaf = true;
		b->cost[i] = prim_cost < box_cost ? prim_cost : box_cost;
		++i;
	}
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
	return (false);
}
