#include <rt_tree.h>
#include <malloc.h>

static bool	init_tree(t_rttree **dst, uint32_t length)
{
	t_rttree	*tree;
	uint8_t		node_depth;
	size_t		mem_req[3];

	node_depth = 1;
	while (length > ((1u << node_depth) - 1) * LEAF_SIZE)
	{
		length -= 1 << (node_depth - 1);
		node_depth++;
	}
	mem_req[0] = sizeof(t_rttree);
	mem_req[1] = ((1 << node_depth) - 1) * sizeof(t_rtnode);
	mem_req[2] = (1 << (node_depth - 1)) * sizeof(t_point *) * LEAF_SIZE;
	tree = malloc(mem_req[0] + mem_req[1] + mem_req[2]);
	if (!tree)
		return (false);
	tree->root_node = NULL;
	tree->nodes = ((void *) tree) + mem_req[0];
	tree->leafs = ((void *) tree) + mem_req[0] + mem_req[1];
	*dst = tree;
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

t_rttree	*new_tree(t_point *points[], uint32_t length)
{
	t_treeb		builder;

	builder.objs = points;
	builder.idxs = presort_data(points, length);
	if (builder.idxs == NULL)
		return (NULL);
	if (init_tree(&builder.tree, length))
		return (free(builder.idxs), NULL);
	print_shit(&builder);
	builder.tree->root_node = new_node(&builder, 0, length - 1, 0);
	free(builder.idxs);
	if (builder.tree->root_node == NULL)
		return (free(builder.tree), NULL);
	return (builder.tree);
}
