/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <scene.h>
#include <x86intrin.h>
#include <math.h>

static inline uint32_t	merge_size(uint32_t len)
{
	const double	c = pow(DELTA, 0.5 + EPSI) / 2;

	return ((uint32_t)(c * pow((double) len, 0.5 - EPSI)) + 1);
}

static void	calc_leaf_areas(
		const t_bvhbuilder *b,
		const uint32_t start,
		const uint32_t len)
{
	uint32_t	i;
	uint32_t	j;
	t_cluster	*ci;
	t_cluster	*cj;

	i = start;
	while (i < start + len)
	{
		ci = b->clusters + b->nodes[i];
		j = start;
		while (j < i)
		{
			cj = b->clusters + b->nodes[j];
			b->area[i][j] = combo_sa(ci->aabb, cj->aabb);
			if (b->area[i][j] < b->min_info[i].min_area)
				b->min_info[i] = (t_minfo){b->area[i][j], j, b->nodes[j]};
			if (b->area[i][j] < b->min_info[j].min_area)
				b->min_info[j] = (t_minfo){b->area[i][j], i, b->nodes[i]};
			++j;
		}
		++i;
	}
}

static uint32_t	create_leafs(
		t_bvhbuilder *b,
		const uint32_t start,
		const uint32_t lo,
		const uint32_t hi)
{
	const uint32_t	len = hi - lo + 1;
	uint32_t		i;

	i = 0;
	while (i < len)
	{
		b->nodes[start + i] = b->keys[lo + i].idx;
		b->clusters[b->nodes[start + i]] = (t_cluster){
			.aabb = calc_bounds(b->prims + b->nodes[start + i]),
			.len = 1
		};
		b->min_info[start + i].min_area = INFINITY;
		++i;
	}
	calc_leaf_areas(b, start, len);
	return (merge_nodes(b, start, len, merge_size(len)));
}

static void	merge_clusters(
		const t_bvhbuilder *b,
		const uint32_t start,
		const uint32_t len[3])
{
	uint32_t	i;
	uint32_t	j;
	t_cluster	*ci;
	t_cluster	*cj;

	i = start;
	while (i < start + len[0])
	{
		ci = b->clusters + b->nodes[i];
		j = start + len[0];
		while (j < start + len[2])
		{
			cj = b->clusters + b->nodes[j];
			b->area[j][i] = combo_sa(ci->aabb, cj->aabb);
			if (b->area[j][i] < b->min_info[i].min_area)
				b->min_info[i] = (t_minfo){b->area[j][i], j, b->nodes[j]};
			if (b->area[j][i] < b->min_info[j].min_area)
				b->min_info[j] = (t_minfo){b->area[j][i], i, b->nodes[i]};
			++j;
		}
		++i;
	}
}

uint32_t	cluster_td(
		t_bvhbuilder *b,
		uint32_t start,
		uint32_t lo,
		uint32_t hi)
{
	const uint32_t	lims[2] = {lo, hi};
	const uint32_t	bit = 1 << (31 - _lzcnt_u32(b->keys[hi].key));
	uint32_t		len[3];

	if (lo >= hi)
		return (0);
	if ((hi - lo + 1) <= DELTA)
		return (create_leafs(b, start, lo, hi));
	while (hi != lo + 1)
	{
		if (b->keys[(lo + hi) >> 1].key & bit)
			hi = (lo + hi) >> 1;
		else
			lo = (lo + hi) >> 1;
	}
	if (lo == lims[0] || hi == lims[1])
		lo = (lims[0] + lims[1]) >> 1;
	len[0] = cluster_td(b, start, lims[0], lo);
	len[1] = cluster_td(b, start + len[0], lo + 1, lims[1]);
	len[2] = len[0] + len[1];
	merge_clusters(b, start, len);
	return (merge_nodes(b, start, len[2], merge_size(len[2])));
}
