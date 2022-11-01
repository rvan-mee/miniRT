/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_node.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/10 18:32:19 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <rt_tree.h>
#include <ft_math.h>
#include <libft.h>

static inline t_point	*get_point(
		const t_treeb *b,
		const uint8_t sort_axis,
		const uint32_t index)
{
	return (b->objs[b->idxs[sort_axis][index]]);
}

static t_rtnode	*init_leaf(
		t_rtnode *node,
		t_treeb *b,
		const uint32_t min)
{
	uint8_t	i;

	node->points = b->tree->leafs + b->leaf_i;
	b->leaf_i += LEAF_SIZE;
	i = node->size;
	while (i--)
		node->points[i] = get_point(b, node->axis, i + min);
	return (node);
}

static inline void	do_part(
		const t_treeb *b,
		const uint8_t axis,
		t_pdata pdata)
{
	const uint32_t	med = pdata.med;
	int				comparison;
	uint32_t		i;
	t_point			*point;

	++pdata.med;
	i = pdata.min;
	while (i <= pdata.max)
	{
		point = b->objs[pdata.src[i]];
		comparison = compare_points(point->pos, pdata.pivot, axis);
		if (comparison == 0)
			pdata.dst[med] = pdata.src[i];
		else if (comparison > 0)
			pdata.dst[pdata.med++] = pdata.src[i];
		else
			pdata.dst[pdata.min++] = pdata.src[i];
		++i;
	}
}

static void	partition(
		const t_treeb *b,
		const uint32_t min,
		const uint32_t max,
		const t_rtnode *node)
{
	t_pdata			pdata;

	pdata = (t_pdata){
		.pivot = node->point->pos,
		.min = min, .med = (max + min) / 2, .max = max,
		.src = b->idxs[3],
		.axis = node->axis
	};
	while (true)
	{
		pdata.axis = (pdata.axis + 1) % 3;
		if (pdata.axis == node->axis)
			break ;
		pdata.dst = b->idxs[pdata.axis];
		ft_memcpy(
			pdata.src + min,
			pdata.dst + min,
			node->size * sizeof(uint32_t));
		do_part(b, node->axis, pdata);
	}
}

t_rtnode	*new_node(
		t_treeb *b,
		const uint32_t min,
		const uint32_t max,
		const uint8_t depth)
{
	t_rtnode	*node;
	uint8_t		ax;

	node = b->tree->nodes + b->node_i++;
	node->size = max - min + 1;
	node->axis = depth % 3;
	ax = 3;
	while (ax--)
	{
		node->bounds.min[ax] = get_point(b, ax, min)->pos[ax];
		node->bounds.max[ax] = get_point(b, ax, max)->pos[ax];
	}
	node->is_leaf = node->size <= LEAF_SIZE;
	if (node->is_leaf)
		return (init_leaf(node, b, min));
	node->point = get_point(b, node->axis, (min + max) / 2);
	partition(b, min, max, node);
	node->l = new_node(b, min, (min + max) / 2 - 1, depth + 1);
	node->r = new_node(b, (min + max) / 2 + 1, max, depth + 1);
	if (!(node->l || node->r))
		return (NULL);
	return (node);
}
