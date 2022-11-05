/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aac_merge.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>
#include <math.h>

static void	update_area(
		const t_bvhbuilder *b,
		const uint32_t node,
		const uint32_t lo,
		const uint32_t hi)
{
	uint32_t	i;

	b->min_info[node].min_area = INFINITY;
	i = lo;
	while (i < node)
	{
		if (b->area[node][i] < b->min_info[node].min_area)
			b->min_info[node] = (t_minfo){b->area[node][i], i, b->nodes[i]};
		++i;
	}
	i = node + 1;
	while (i < hi)
	{
		if (b->area[i][node] < b->min_info[node].min_area)
			b->min_info[node] = (t_minfo){b->area[i][node], i, b->nodes[i]};
		++i;
	}
}

static void	calc_area_after_merge(
		const t_bvhbuilder *b,
		const uint32_t node,
		const uint32_t start,
		const uint32_t len)
{
	const t_aabb	new_bounds = b->clusters[b->node_idx].aabb;
	uint32_t		i;

	i = start;
	while (i < node)
	{
		b->area[node][i] = combo_sa(new_bounds, b->clusters[b->nodes[i]].aabb);
		++i;
	}
	i = node + 1;
	while (i < start + len)
	{
		b->area[i][node] = combo_sa(new_bounds, b->clusters[b->nodes[i]].aabb);
		++i;
	}
}

static void	move_area_after_merge(
		const t_bvhbuilder *b,
		const uint32_t node,
		const uint32_t start,
		const uint32_t len)
{
	uint32_t	i;

	i = start;
	while (i < node)
	{
		b->area[node][i] = b->area[start + len][i];
		++i;
	}
	i = node + 1;
	while (i < start + len)
	{
		b->area[i][node] = b->area[start + len][i];
		++i;
	}
}

// Assignment to comb is to stop gcc from complaining
static void	find_best_merge(
		const t_bvhbuilder *b,
		const uint32_t start,
		const uint32_t len,
		uint32_t comb[2])
{
	float		min_area;
	uint32_t	i;

	comb[0] = 0;
	comb[1] = 1;
	min_area = INFINITY;
	i = start;
	while (i < start + len)
	{
		if (b->min_info[i].min_pos == start + len)
			b->min_info[i].min_node = -1;
		if (b->min_info[i].min_node != b->nodes[b->min_info[i].min_pos])
			update_area(b, i, start, start + len);
		if (b->min_info[i].min_area < min_area)
		{
			min_area = b->min_info[i].min_area;
			comb[0] = i;
			comb[1] = b->min_info[i].min_pos;
		}
		++i;
	}
}

uint32_t	merge_nodes(
		t_bvhbuilder *b,
		const uint32_t start,
		uint32_t len,
		const uint32_t new_len)
{
	t_nodeidx	comb[2];
	t_cluster	*c[2];

	while (len > new_len)
	{
		find_best_merge(b, start, len, comb);
		c[0] = b->clusters + b->nodes[comb[0]];
		c[1] = b->clusters + b->nodes[comb[1]];
		b->clusters[b->node_idx] = (t_cluster){
			{{b->nodes[comb[0]], b->nodes[comb[1]]}},
			aabb_combine(c[0]->aabb, c[1]->aabb),
			c[0]->len + c[1]->len,
			false
		};
		calc_area_after_merge(b, comb[0], start, len);
		len -= 1;
		move_area_after_merge(b, comb[1], start, len);
		b->nodes[comb[0]] = b->node_idx;
		b->nodes[comb[1]] = b->nodes[start + len];
		b->min_info[comb[1]] = b->min_info[start + len];
		++b->node_idx;
	}
	return (len);
}
