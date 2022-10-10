#include <rt_tree.h>
#include <malloc.h>
#include <assert.h>
#include "libft.h"
#include "ft_math.h"

static bool	init_tree(t_rttree **dst, uint32_t length)
{
	t_rttree	*tree;
	uint8_t		node_depth;

	tree = malloc(sizeof(t_rttree));
	if (!tree)
		return (false);
	*dst = tree;
	tree->length = length;
	node_depth = 1;
	while (length > ((1u << node_depth) - 1) * LEAF_SIZE)
	{
		length -= 1 << (node_depth - 1);
		node_depth++;
	}
	if (!dynarr_create(&tree->nodes, (1 << node_depth) - 1, sizeof(t_rtnode)) || \
		!dynarr_create(&tree->leafs, (1 << (node_depth - 1)) * LEAF_SIZE, sizeof(t_point *)))
		return (/*destroy_tree(tree), */false);
	return (true);
}

static void	print_shit(t_treeb *b)
{
	uint32_t	i;

	i = 0;
	while (i < b->tree->length)
	{
		printf("[%2u] (%.1f, %.1f, %.1f)\t%u\t%u\t%u\n", i,
				b->objs[i]->pos[0], b->objs[i]->pos[1], b->objs[i]->pos[2],
				b->idxs[0][i], b->idxs[1][i], b->idxs[2][i]);
		++i;
	}
}

static t_rtnode	*init_leaf(t_rtnode *node, t_treeb *b, uint32_t min)
{
	uint8_t	i;

	node->leaf.points = dynarr_get_u(&b->tree->leafs, b->tree->leafs.length);
	b->tree->leafs.length += LEAF_SIZE;
	i = node->size;
	while (i--)
		node->leaf.points[i] = b->objs[b->idxs[node->axis][i + min]];
	return (node);
}

static inline t_point	*get_point(t_treeb *b, uint8_t sort_axis, uint32_t index)
{
	return (b->objs[b->idxs[sort_axis][index]]);
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
	assert(pdata->med == pdata->max + 1 && "maybe good to check");
	assert(pdata->min == med && "This should be the same");
}

void	partition(t_treeb *b, const uint32_t min, const uint32_t max, const uint8_t axis)
{
	t_pdata			pdata;

	printf("Partitioning: %u %u %u\n", min, max, axis);
	pdata.pivot = get_point(b, axis, (max + min) / 2)->pos;
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
		ft_memcpy(pdata.src + min, pdata.dst + min,
				(max - min + 1) * sizeof(uint32_t));
		do_part(b, &pdata, axis);

	}
	print_shit(b);
}

t_rtnode	*new_node(t_treeb *b, uint32_t min, uint32_t max, uint8_t depth)
{
	t_rtnode	*node;

	if (b->tree->nodes.capacity <= b->tree->nodes.length)
		dprintf(2, "We're trying to create too many nodes?! This should nut be happening\n");
	node = dynarr_get(&b->tree->nodes, b->tree->nodes.length++);
	node->size = max - min + 1;
	node->axis = depth % 3;
	node->is_leaf = node->size <= LEAF_SIZE;
	if (node->is_leaf)
		return (init_leaf(node, b, min));
	partition(b, min, max, node->axis);
	node->node.point = b->objs[b->idxs[node->axis][(min + max) / 2]];
	node->min = (t_fvec){
		get_point(b, X, min)->pos[X],
		get_point(b, Y, min)->pos[Y],
		get_point(b, Z, min)->pos[Z]
	};
	node->max = (t_fvec){
		get_point(b, X, max)->pos[X],
		get_point(b, Y, max)->pos[Y],
		get_point(b, Z, max)->pos[Z]
	};
	node->node.l = new_node(b, min, (min + max) / 2 - 1, depth + 1);
	node->node.r = new_node(b, (min + max) / 2 + 1, max, depth + 1);
	if (!(node->node.l || node->node.r))
		return (/*destroy_node(node), */NULL);
	return (node);
}

t_rttree	*new_tree(t_point *points[], uint32_t length)
{
	t_treeb		builder;

	builder.objs = points;
	builder.idxs = presort_data(points, length);
	if (builder.idxs == NULL)
		return (NULL);
	if (!init_tree(&builder.tree, length))
		return (free(builder.idxs)/*, destroy_tree(builder.tree)*/, NULL);
	print_shit(&builder);
	builder.tree->root_node = new_node(&builder, 0, length - 1, 0);
	return (builder.tree);
}