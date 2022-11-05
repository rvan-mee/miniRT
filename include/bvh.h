/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bvh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H
# include <minirt.h>

# ifndef AAC_FAST
#  define EPSI	0.1
#  define DELTA	20
# else
#  define EPSI	0.2
#  define DELTA	4
# endif

// An index into either t_bvh.clusters or t_bvh_b.clusters
typedef uint32_t				t_nodeidx;
// An index in the prim array
typedef uint32_t				t_objidx;

// A morton code, saving the objects original index and the morton
// representation of its coordinates
typedef struct s_morton {
	uint32_t	key;
	t_objidx	idx;
}	t_morton;

// A node in the hierarchy
typedef struct s_cluster {
	t_nodeidx	l;
	t_nodeidx	r;
	t_aabb		aabb;
	uint32_t	len;
	bool		leaf;
}	t_cluster;

// Temporary info for all clusters, storing the closest node
// min_area is the combined surface area of this node, and the min node
// min_pos is the index of the node in builder->nodes (and area, and min_info)
// min_node is the index of the node in builder->clusters
typedef struct s_min_info {
	float		min_area;
	uint32_t	min_pos;
	t_nodeidx	min_node;
}	t_minfo;

// Data struct used while building a new bounding volume hierarchy
typedef struct s_bvh_b {
	t_object	*prims;
	t_cluster	*clusters;
	t_morton	*keys;
	t_nodeidx	*nodes;
	float		**area;
	uint32_t	*cost;
	float		*surface_area;
	t_minfo		*min_info;
	t_nodeidx	node_idx;
	uint32_t	length;
}	t_bvhbuilder;

typedef struct s_priority_queue	t_prio;
struct s_priority_queue {
	t_nodeidx	cluster;
	float		dist;
	t_prio		*next;
};

/**
 * Create a new bounding volume hierarchy using approximate agglomerative
 * clustering. Tons of credit (and hate) to:
 * http://graphics.cs.cmu.edu/projects/aac/aac_build.pdf
 *
 * @param objects[in] All primitives in the scene
 * @param length[in] The amount of primitives in the scene
 * @param dst[out] A pointer to a t_bvh where the resulting bvh should be stored
 *
 * @return `true' on success, `false' on failure
 *
 * If true has been returned, the caller should free dst->clusters!
 */
bool		new_bvh(t_object objects[], uint32_t length, t_bvh *dst);

/**
 * Generate morton codes for all primitives in the prims array of the builder.
 *
 * Uses the parallel bit deposit instruction (_pdep_u32) to make things easier
 */
void		generate_codes(const t_bvhbuilder *b);

/**
 * Sort generated morton codes (in ascending order)
 *
 * Uses radix sort!
 */
bool		sort_codes(t_morton codes[], uint32_t length);

/**
 * Recursively split all primitive clusters into chunks, up until <= DELTA
 * primitives remain. Greedily combines those nodes until only a small amount
 * remains.
 *
 * @param b[in/out] the BVH builder
 * @param start[in] The partition index in the temporary data arrays
 * @param lo[in] The lowest primitive index we want to include (morton array)
 * @param hi[in] The highest primitive index we want to include (morton array)
 *
 * @return The amount of clusters remaining after merging them.
 */
uint32_t	cluster_td(
				t_bvhbuilder *b,
				uint32_t start,
				uint32_t lo,
				uint32_t hi);

uint32_t	merge_nodes(
				t_bvhbuilder *b,
				uint32_t start,
				uint32_t len,
				uint32_t new_len);

bool		flatten_bvh(t_bvhbuilder *b);

#endif