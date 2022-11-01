/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   morton.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 15:00:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/01 15:00:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <bvh.h>
#include <libft.h>
#include <x86intrin.h>
#include <math.h>

#define MORTON_BITS		30
#define RADIX_PASSES	6

static inline void	create_key(
		const t_bvhbuilder *b,
		const t_objidx i,
		const t_aabb lims)
{
	const t_fvec	size = lims.max - lims.min;
	const t_fvec	pos = (b->prims[i]->coords - lims.min) / size;
	const uint16_t	xyz[3] = {
		(uint16_t)(pos[X] * 0b1111111111),
		(uint16_t)(pos[Y] * 0b1111111111),
		(uint16_t)(pos[Z] * 0b1111111111),
	};

	b->keys[i].idx = i;
	b->keys[i].key = 0;
	b->keys[i].key |= _pdep_u32(xyz[X], 0x24924924);
	b->keys[i].key |= _pdep_u32(xyz[Y], 0x12492492);
	b->keys[i].key |= _pdep_u32(xyz[Z], 0x09249249);
}

void	generate_codes(const t_bvhbuilder *b)
{
	t_aabb		bounds;
	uint32_t	i;
	uint8_t		j;

	bounds.min = (t_fvec){INFINITY, INFINITY, INFINITY};
	bounds.max = (t_fvec){-INFINITY, -INFINITY, -INFINITY};
	i = 0;
	while (i < b->length)
	{
		j = 0;
		while (j < 3)
		{
			bounds.max[j] = fmaxf(bounds.max[j], b->prims[i]->coords[j]);
			bounds.min[j] = fminf(bounds.min[j], b->prims[i]->coords[j]);
			++j;
		}
		++i;
	}
	i = 0;
	while (i < b->length)
		create_key(b, i++, bounds);
}

static const uint8_t	g_bits_per_pass = MORTON_BITS / RADIX_PASSES;
static const uint8_t	g_num_buckets = 1 << g_bits_per_pass;
static const uint8_t	g_mask = g_num_buckets - 1;

static inline void	get_bucket_offsets(
		const t_morton src[],
		uint32_t buckets[2][g_num_buckets],
		uint32_t length,
		uint8_t pass)
{
	uint32_t	i;
	uint8_t		bucket;

	i = 0;
	while (i < length)
	{
		bucket = (src[i].key >> (pass * g_bits_per_pass)) & g_mask;
		buckets[0][bucket]++;
		i++;
	}
	i = 1;
	while (i < g_num_buckets)
	{
		buckets[1][i] = buckets[1][i - 1] + buckets[0][i - 1];
		++i;
	}
}

static inline void	move_codes(
		t_morton *arrs[],
		uint32_t buckets[2][g_num_buckets],
		const uint32_t length,
		const uint8_t pass)
{
	t_morton	*src;
	t_morton	*dst;
	uint32_t	i;
	uint8_t		bucket;

	src = arrs[pass & 1];
	dst = arrs[!(pass & 1)];
	i = 0;
	while (i < length)
	{
		bucket = (src[i].key >> (pass * g_bits_per_pass)) & g_mask;
		dst[buckets[1][bucket]] = src[i];
		buckets[1][bucket]++;
		++i;
	}
}

// 32 in buckets is g_num_buckets, but norminette didnt like
bool	sort_codes(t_morton codes[], uint32_t length)
{
	t_morton	*arrs[2];
	uint32_t	buckets[2][32];
	uint8_t		pass;

	arrs[0] = codes;
	arrs[1] = malloc(length * sizeof(t_morton));
	if (arrs[1] == NULL)
		return (false);
	pass = 0;
	while (pass < RADIX_PASSES)
	{
		ft_bzero(buckets, sizeof(buckets));
		get_bucket_offsets(arrs[pass & 1], buckets, length, pass);
		move_codes(arrs, buckets, length, pass);
		++pass;
	}
	free(arrs[1]);
	return (true);
}
