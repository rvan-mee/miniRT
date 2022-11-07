/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_tree.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 18:32:19 by lsinke        #+#    #+#                 */
/*   Updated: 2022/10/10 18:32:19 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TREE_H
# define RT_TREE_H

# include <dynarr.h>
# include <minirt.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# define LEAF_SIZE	8

typedef struct s_point {
	t_fvec	pos;
}	t_point;

typedef struct s_rtnode	t_rtnode;
struct s_rtnode {
	union {
		struct {
			t_point		*point;
			t_rtnode	*l;
			t_rtnode	*r;
		};
		union {
			t_point		**points;
			t_object	**objects;
		};
	};
	t_aabb		bounds;
	uint32_t	size;
	uint8_t		axis;
	bool		is_leaf;
	bool		is_bvh;
};

typedef struct s_rttree {
	t_rtnode	*root_node;
	t_rtnode	*nodes;
	t_point		**leafs;
	uint32_t	length;
}	t_rttree;

typedef struct s_bounds {
	t_object	**infinite_objects;
	t_rttree	*tree;
}	t_bounds;

typedef struct s_treedat {
	t_point		**objs;
	uint32_t	**sorted;
	uint32_t	len;
	uint8_t		dim;
}	t_rtdat;

typedef struct s_treebuilder {
	t_point			**objs;
	uint32_t		**idxs;
	uint32_t		node_i;
	uint32_t		leaf_i;
	t_rttree		*tree;
}	t_treeb;

typedef struct s_partdata {
	t_fvec		pivot;
	uint32_t	min;
	uint32_t	med;
	uint32_t	max;
	uint32_t	*src;
	uint32_t	*dst;
	uint8_t		axis;
}	t_pdata;

/**
 * Construct a new 3d tree.
 *
 * Returns `NULL` If an error occurred during construction.
 *
 * This function _should_ construct the tree in O(3Nlog(N)) time, by sorting
 * all points only once, and keeping their indices sorted.
 *
 * Credit: https://arxiv.org/abs/1410.5420
 *
 * The newly constructed tree can be destroyed
 * by just calling free() on the pointer returned by this function.
 */
t_rttree	*new_tree(t_point *points[], uint32_t length);
/**
 * Recursively construct a node and its' children.
 *
 * If the amount of points for this node gets below LEAF_SIZE, the new
 * node will be a leaf node. This means it contains up to LEAF_SIZE points,
 * sorted along the super key of the axis of the node (So, if depth % 3 == Y,
 * the points inside the node will be sorted ascending in yzx).
 *
 * If the node is not a leaf, it splits all points up along the median of the
 * splitting axis, and sets that point as node.point, then recursively creates
 * the left and right nodes.
 */
t_rtnode	*new_node(t_treeb *b, uint32_t min, uint32_t max, uint8_t depth);
/**
 * Does not actually sort the points, but allocates 4 index arrays.
 *
 *  idx 1) Indices of the original points, sorted by xyz
 *  idx 2) Indices of the original points, sorted by yzx
 *  idx 3) Indices of the original points, sorted by zxy
 *  idx 4) Temporary index array, used in partitioning.
 */
uint32_t	**presort_data(t_point *points[], uint32_t length);

#endif