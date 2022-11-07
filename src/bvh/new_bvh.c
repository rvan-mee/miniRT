/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_bvh.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/10 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/12/10 18:32:19 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <libft.h>
#include <bvh.h>
#include <stdio.h>

static inline uint32_t	get_alloc_req(uint32_t n)
{
	const double	c = (float) pow(DELTA, 0.5 + EPSI) / 2;

	return ((uint32_t)(4 * c * pow(n, 0.5 - EPSI / 2) + 1e-5) + 1);
}

static void	free_builder(t_bvhbuilder *b, bool success)
{
	t_nodeidx	i;

	free(b->min_info);
	free(b->nodes);
	free(b->keys);
	free(b->area);
	free(b->aabb_sa);
	free(b->cost[0]);
	free(b->cost[1]);
	if (success)
		return ;
	i = b->length;
	while (i < b->node_idx)
		if (b->clusters[i].leaf)
			free(b->clusters[i].prims);
	free(b->clusters);
}

static bool	alloc_builder(t_bvhbuilder *b, uint32_t n)
{
	const uint32_t	req = get_alloc_req(n);
	const size_t	row_size = req * sizeof(float);
	const size_t	ptr_size = req * sizeof(float *);
	uint32_t		i;

	b->keys = ft_calloc(n, sizeof(t_morton));
	b->area = ft_calloc(req * row_size + ptr_size, 1);
	b->min_info = ft_calloc(req, sizeof(t_minfo));
	b->nodes = ft_calloc(2 * n, sizeof(uint32_t));
	b->clusters = ft_calloc(2 * n, sizeof(t_cluster));
	b->cost[0] = ft_calloc(2 * n, sizeof(float));
	b->cost[1] = ft_calloc(2 * n, sizeof(float));
	b->aabb_sa = ft_calloc(2 * n, sizeof(float));
	if (!b->keys || !b->nodes || !b->area || !b->min_info || !b->clusters
		|| !b->cost[0] || !b->cost[1] || !b->aabb_sa)
		return (free_builder(b, false), false);
	i = 0;
	while (i < req)
	{
		b->area[i] = ((void *) b->area) + i * row_size + ptr_size;
		++i;
	}
	return (true);
}

uint16_t	print_nodes(t_bvh *b, uint16_t depth, uint32_t node)
{
	static uint16_t	maxdepth = 0;

	maxdepth = depth > maxdepth ? depth : maxdepth;
	dprintf(1, "node %u (len=%u) %s (%.1f,%.1f,%.1f)-(%.1f,%.1f,%.1f)\n",
			node, b->clusters[node].len, b->clusters[node].leaf ? "(leaf)" : "",
			b->clusters[node].aabb.min[X], b->clusters[node].aabb.min[Y], b->clusters[node].aabb.min[Z],
			b->clusters[node].aabb.max[X], b->clusters[node].aabb.max[Y], b->clusters[node].aabb.max[Z]);
	if (b->clusters[node].leaf)
	{
		for (uint16_t n = depth + 1; n > 0; n--)
			dprintf(1, "  ");
		for (uint32_t i = 0; i < b->clusters[node].len; i++)
			dprintf(1, "%u ", b->clusters[node].prims[i]);
		dprintf(1, "\n");
		return (maxdepth);
	}
	if (b->clusters[node].len == 1)
		return (maxdepth);
	for (uint16_t n = depth + 1; n > 0; n--)
		dprintf(1, "  ");
	dprintf(1, "l: ");
	print_nodes(b, depth + 1, b->clusters[node].l);
	for (uint16_t n = depth + 1; n > 0; n--)
		dprintf(1, "  ");
	dprintf(1, "r: ");
	print_nodes(b, depth + 1, b->clusters[node].r);
	return (maxdepth);
}

bool	new_bvh(t_object objects[], uint32_t length, t_bvh *dst)
{
	t_bvhbuilder	builder;
	uint32_t		final_len;
	bool			success;

	builder.prims = objects;
	builder.length = length;
	builder.node_idx = length;
	if (!alloc_builder(&builder, length))
		return (NULL);
	generate_codes(&builder);
	success = sort_codes(builder.keys, length);
	if (success)
	{
		final_len = cluster_td(&builder, 0, 0, length - 1);
		merge_nodes(&builder, 0, final_len, 1);
		*dst = (t_bvh){objects, builder.clusters, builder.node_idx - 1, length};
	}
	flatten_bvh(&builder);
	free_builder(&builder, success);
	//dprintf(1, "maxdepth = %u\n", print_nodes(dst, 0, dst->root));
	return (success);
}
