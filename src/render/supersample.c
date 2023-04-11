/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   supersample.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 18:44:29 by lsinke        #+#    #+#                 */
/*   Updated: 2023/04/10 18:44:29 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <x86intrin.h>

static bool	count_hits(t_hit hits[], int32_t hit_n, t_sinfo *info)
{
	uint8_t	i;
	uint8_t	j;

	i = 16 - __lzcnt16(info->counted);
	if (i == hit_n)
		return (true);
	while (i < hit_n)
	{
		if ((info->counted & (1 << i)) == 0)
		{
			info->hit_cnt[i]++;
			info->counted |= (1 << i);
			j = i;
			while (++j < hit_n)
			{
				if (info->counted & (1 << j)
					|| hits[i].object != hits[j].object)
					continue ;
				info->hit_cnt[i]++;
				info->counted |= (1 << j);
			}
		}
		++i;
	}
	return (false);
}

/**
 * This is the exit condition for adaptive super sampling.
 *
 * Sample count | Max object count
 * 2 | 1
 * 4 | 2
 * 8 | 4
 */
static bool	enough_hits(t_sinfo *info, int32_t sample, int32_t hit_n)
{
	int32_t	obj_count;
	int32_t	i;

	if (count_hits(info->hits, hit_n, info))
		return (true);
	if (info->hit_cnt[0] == hit_n)
		return (true);
	if (sample == 2)
		return (false);
	obj_count = 0;
	if (hit_n != sample)
		++obj_count;
	i = 0;
	while (i < hit_n)
		if (info->hit_cnt[i++] != 0)
			++obj_count;
	if (sample == 4)
		return (obj_count <= 2);
	return (obj_count <= 4);
}

/*
 * 0-1: 2x super sampling
 * 0-3: 4x
 * 0-7: 8x
 * 0-15: 16x
 */
static const t_fvec2	g_aa_offs[] = {\
	{0.35f, 0.05f}, {0.65f, 0.95f}, \
	{0.05f, 0.65f}, {0.95f, 0.35f}, \
	{0.45f, 0.35f}, {0.55f, 0.65f}, {0.35f, 0.55f}, {0.65f, 0.45f}, \
	{0.55f, 0.15f}, {0.45f, 0.85f}, {0.15f, 0.45f}, {0.85f, 0.55f}, \
	{0.75f, 0.25f}, {0.25f, 0.75f}, {0.25f, 0.25f}, {0.75f, 0.75f}, \
};

/**
 * Keep casting rays, until a specific exit condition depending on aa settings
 * is reached:
 *
 * MAX_SAMPLES reached.
 *
 * SMART_AA (adaptive super sampling) is enabled, and most samples hit the
 * same objects.
 */
void	cast_cam_rays(t_scene *scene, t_sinfo *info, int32_t x, int32_t y)
{
	int32_t	sample;
	int32_t	hit_n;
	t_fvec2	pos;

	hit_n = 0;
	sample = 0;
	while (sample < MAX_SAMPLES)
	{
		pos = (t_fvec2){(float) x, (float) y} + g_aa_offs[sample++];
		info->hits[hit_n].ray = get_cam_ray(&scene->camera, pos[X], pos[Y]);
		info->hits[hit_n].inside_ri = 1.0f;
		if (trace(scene, &info->hits[hit_n].ray, info->hits + hit_n))
			++hit_n;
		if (SMART_AA && (sample == 2 || sample == 4 || sample == 8)
			&& enough_hits(info, sample, hit_n))
			break ;
	}
	count_hits(info->hits, hit_n, info);
	info->sample_count = sample;
	info->hit_count = hit_n;
}

/**
 * Shade some samples, and return the colour.
 *
 * If CHEAP_AA is enabled, every object will only be shaded once.
 */
t_fvec	shade_samples(t_scene *scene, t_sinfo *info)
{
	t_fvec	col;
	t_hit	*hit;
	uint8_t	i;
	uint8_t	weight;

	col = (t_fvec){};
	i = 0;
	while (i < info->hit_count)
	{
		if (CHEAP_AA)
			weight = info->hit_cnt[i];
		else
			weight = 1;
		if (weight != 0)
		{
			hit = info->hits + i;
			col += shade(scene, hit, 1.0f) * (float) weight;
		}
		++i;
	}
	return (col / (float) info->sample_count);
}
