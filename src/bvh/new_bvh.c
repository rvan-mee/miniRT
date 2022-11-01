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
#include "libft.h"
#include "ft_math.h"
#include <bvh.h>

static inline uint32_t	get_alloc_req(uint32_t n)
{
	const double	c = (float) pow(DELTA, 0.5 + EPSI) / 2;

	return ((uint32_t)(4 * c * pow(n, 0.5 - EPSI / 2) + 1e-5) + 1);
}

static void	free_builder(t_bvhbuilder *b, bool success)
{
	free(b->min_info);
	free(b->nodes);
	free(b->keys);
	free(b->area);
	if (!success)
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
	if (!b->keys || !b->nodes || !b->area || !b->min_info || !b->clusters)
	{
		free_builder(b, false);
		return (false);
	}
	i = 0;
	while (i < req)
	{
		b->area[i] = ((void *) b->area) + i * row_size + ptr_size;
		++i;
	}
	return (true);
}

bool	new_bvh(t_object *objects[], uint32_t length, t_bvh *dst)
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
	free_builder(&builder, success);
	return (success);
}
