#include <rt_tree.h>
#include <ft_math.h>
#include <libft.h>

static inline t_point	*get_point(t_treeb *b, uint8_t sort_axis, uint32_t index)
{
	return (b->objs[b->idxs[sort_axis][index]]);
}

static t_rtnode	*init_leaf(t_rtnode *node, t_treeb *b, uint32_t min)
{
	uint8_t	i;

	node->leaf.points = b->tree->leafs + b->leaf_i;
	b->leaf_i += LEAF_SIZE;
	i = node->size;
	while (i--)
		node->leaf.points[i] = get_point(b, node->axis, i + min);
	return (node);
}

static inline void	do_part(t_treeb *b, t_pdata *pdata, uint8_t axis)
{
	const uint32_t	med = pdata->med;
	int				comparison;
	uint32_t		i;
	t_point			*point;

	++pdata->med;
	i = pdata->min;
	while (i <= pdata->max)
	{
		point = b->objs[pdata->src[i]];
		comparison = compare_points(point->pos, pdata->pivot, axis);
		if (comparison == 0)
			pdata->dst[med] = pdata->src[i];
		else if (comparison > 0)
			pdata->dst[pdata->med++] = pdata->src[i];
		else
			pdata->dst[pdata->min++] = pdata->src[i];

		++i;
	}
}

static void	partition(t_treeb *b, const uint32_t min, const uint32_t max, t_rtnode *node)
{
	const uint8_t	axis = node->axis;
	t_pdata			pdata;

	pdata.pivot = node->node.point->pos;
	pdata.src = b->idxs[3];
	pdata.axis = axis;
	while (true)
	{
		pdata.axis = (pdata.axis + 1) % 3;
		if (pdata.axis == axis)
			break ;
		pdata.dst = b->idxs[pdata.axis];
		pdata.min = min;
		pdata.med = (max + min) / 2;
		pdata.max = max;
		ft_memcpy(
				pdata.src + min,
				pdata.dst + min,
				(max - min + 1) * sizeof(uint32_t));
		do_part(b, &pdata, axis);
	}
}

t_rtnode	*new_node(t_treeb *b, uint32_t min, uint32_t max, uint8_t depth)
{
	t_rtnode	*node;
	uint8_t		ax;

	node = b->tree->nodes + b->node_i++;
	node->size = max - min + 1;
	node->axis = depth % 3;
	ax = 3;
	while (ax--)
	{
		node->min[ax] = get_point(b, ax, min)->pos[ax];
		node->max[ax] = get_point(b, ax, max)->pos[ax];
	}
	node->is_leaf = node->size <= LEAF_SIZE;
	if (node->is_leaf)
		return (init_leaf(node, b, min));
	node->node.point = get_point(b, node->axis, (min + max) / 2);
	partition(b, min, max, node);
	node->node.l = new_node(b, min, (min + max) / 2 - 1, depth + 1);
	node->node.r = new_node(b, (min + max) / 2 + 1, max, depth + 1);
	if (!(node->node.l || node->node.r))
		return (NULL);
	return (node);
}
