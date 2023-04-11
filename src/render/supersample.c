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
#include <strings.h>
#include <x86intrin.h>

/*
 * 1-2: 2x super sampling
 * 1-4: 4x
 * 1-8: 8x
 * 1-16: 16x
 */
static const t_fvec2	g_aa_offs[] = {\
	{0.35f, 0.05f}, {0.65f, 0.95f}, \
	{0.05f, 0.65f}, {0.95f, 0.35f}, \
	{0.45f, 0.35f}, {0.55f, 0.65f}, {0.35f, 0.55f}, {0.65f, 0.45f}, \
	{0.55f, 0.15f}, {0.45f, 0.85f}, {0.15f, 0.45f}, {0.85f, 0.55f}, \
	{0.75f, 0.25f}, {0.25f, 0.75f}, {0.25f, 0.25f}, {0.75f, 0.75f}, \
};

static bool	count_hits(t_hit hits[], int32_t hit_n, t_sinfo *info)
{
	uint8_t	i;
	uint8_t	j;

	i = 16 - __lzcnt16(info->counted);
	if (i == hit_n) // There were no more new samples!
		return (true);
	while (i < hit_n)
	{
		if (!(info->counted & (1 << i)))
		{
			info->hit_cnt[i]++;
			info->counted |= (1 << i);
			j = i + 1;
			while (j < hit_n)
			{
				if (!(info->counted & (1 << j)) && hits[i].object == hits[j].object)
				{
					info->hit_cnt[i]++;
					info->counted |= (1 << j);
				}
				++j;
			}
		}
		++i;
	}
	return (false);
}

// Count how many hits there were for each object
static bool	enough_hits(t_sinfo *info, int32_t sample, int32_t hit_n)
{
	int32_t	obj_count;
	int32_t	i;

	if (count_hits(info->hits, hit_n, info))
		return (true); // no more new samples
	if (info->hit_cnt[0] == hit_n)
		return (true); // all samples hit the same object
	if (sample == 2)
		return (false); // need moar samples
	obj_count = 0;
	if (hit_n != sample)
		++obj_count; // at least 1 sample missed
	i = 0;
	while (i < hit_n)
		if (info->hit_cnt[i++] != 0)
			++obj_count;
	if (sample == 4)
		return (obj_count <= 2);
	return (obj_count <= 4);
}

t_ivec2	cast_cam_rays(t_scene *scene, t_sinfo *info, int32_t x, int32_t y)
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
	return ((t_ivec2){sample, hit_n});
}

t_fvec	shade_samples(t_scene *scene, t_sinfo *samples, int32_t sample_n, int32_t hit_n)
{
	t_fvec	col;
	t_hit	*hit;
	uint8_t	i;

	col = (t_fvec){};
	i = 0;
	while (i < hit_n)
	{
		if (samples->hit_cnt[i] != 0 || CHEAP_AA)
		{
			hit = samples->hits + i;
			col += shade(scene, hit, 1.0f) * (float) (CHEAP_AA || samples->hit_cnt[i]);
		}
		++i;
	}
	return (col / (float) sample_n);
}
