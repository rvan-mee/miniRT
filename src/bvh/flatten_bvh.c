/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flatten_bvh.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 16:24:42 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 16:24:42 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>
#include <math.h>

#ifndef SP_COST
# define SP_COST	0.509f
#endif
#ifndef PL_COST
# define PL_COST	0.526f
#endif
#ifndef CY_COST
# define CY_COST	0.557f
#endif
#ifndef AABB_COST
# define AABB_COST	0.548f
#endif

static void	get_prim_costs(t_bvhbuilder *b, const float costs[])
{
	uint32_t	i;

	i = 0;
	while (i < b->length)
	{
		b->aabb_sa[i] = sa(b->clusters[i].aabb);
		b->cost[0][i] = costs[b->prims[i].type];
		b->cost[1][i] = b->cost[0][i];
		++i;
	}
}

static void	prune_tree(t_bvhbuilder *b)
{
	t_nodeidx	i;
	float		box_cost;
	t_cluster	*clus;

	i = b->length;
	while (i < b->node_idx)
	{
		clus = b->clusters + i;
		b->cost[0][i] = b->cost[0][clus->l] + b->cost[0][clus->r];
		b->aabb_sa[i] = sa(clus->aabb);
		box_cost = AABB_COST;
		box_cost += b->aabb_sa[clus->l] * b->cost[1][clus->l] / b->aabb_sa[i];
		box_cost += b->aabb_sa[clus->r] * b->cost[1][clus->r] / b->aabb_sa[i];
		if (b->cost[0][i] < box_cost)
			clus->leaf = true;
		b->cost[1][i] = fminf(b->cost[0][i], box_cost);
		++i;
	}
}

void	flatten_bvh(t_bvhbuilder *b)
{
	const float	costs[] = {\
		[SPHERE] = SP_COST, \
		[PLANE] = PL_COST, \
		[CYLINDER] = CY_COST
	};

	get_prim_costs(b, costs);
	prune_tree(b);
}
