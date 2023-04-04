/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fresnel.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 22:19:04 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/13 22:19:04 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <ft_math.h>
#include <math.h>
#define CONTRIB_CUTOFF	0.005f

// ri_1 is the refractive index of the material we're leaving, ri_2 entering
static float	reflect_amount(float ri_1, float ri_2, t_hit *hit)
{
	const float	r_0 = powf((ri_1 - ri_2) / (ri_1 + ri_2), 2.0f);
	float		cos_t;
	float		snellius_sq;

	cos_t = -(dot_product(hit->normal, hit->ray.direction));
	if (ri_1 > ri_2)
	{
		snellius_sq = powf(ri_1 / ri_2, 2.0f) * (1.0f - cos_t * cos_t);
		if (snellius_sq > 1)
			return (1.0f);
		cos_t = sqrtf(1.0f - snellius_sq);
	}
	return (r_0 + (1.0f - r_0) * powf(1.0f - cos_t, 5.0f));
}

static float	get_transmittance(const t_mtl *mat)
{
	if (is_flag(mat, DISSOLVED))
		return (1.0f - mat->transp_d);
	else if (is_flag(mat, TRANSPARENT))
		return (mat->transp_tr);
	return (0.0f);
}

static
t_fvec	no_refract(t_scene *scene, t_hit *hit, float contrib, float transm)
{
	t_mtl	*mat;
	t_hit	r_hit;
	t_fvec	colour;

	r_hit.ray = get_biased_ray(hit->hit, hit->ray.direction, hit->normal);
	r_hit.inside_ri = 1.0f;
	if (!trace(scene, &r_hit.ray, &r_hit))
		return ((t_fvec){});
	colour = shade(scene, &r_hit, contrib) * transm;
	mat = hit->object->mat;
	if (is_flag(mat, TRANSMISSION_FILTER))
		colour *= exp_fvec(-mat->tra_filter);
	return (colour);
}

static
t_fvec	transmit_ray(t_scene *scene, t_hit *hit, float contrib, t_fresnel f)
{
	const t_mtl	*mat = hit->object->mat;
	const float	transm = get_transmittance(mat);
	t_hit		r_hit;
	t_fvec		r_dir;
	t_fvec		colour;

	contrib *= transm * (1.0f - f.refl_ratio);
	if (contrib < CONTRIB_CUTOFF)
		return ((t_fvec){});
	if (mat->illum == 4)
		return ((1.0f - f.refl_ratio) * no_refract(scene, hit, contrib, transm));
	r_dir = refract(hit->ray.direction, hit->normal, hit->inside_ri, f.refr_index);
	r_hit.ray = get_biased_ray(hit->hit, r_dir, hit->normal);
	r_hit.inside_ri = f.refr_index;
	if (!trace(scene, &r_hit.ray, &r_hit))
		return ((t_fvec){});
	colour = shade(scene, &r_hit, contrib) * transm;
	if (hit->inside_ri != 1.0f && is_flag(mat, TRANSMISSION_FILTER))
		colour *= exp_fvec(-mat->tra_filter * hit->distance * scene->scale);
	return ((1.0f - f.refl_ratio) * colour);
}

static const float	g_refl_cost = 1.0f / MAX_REFLECTION_DEPTH;
t_fvec	fresnel(t_scene *scene, t_fvec ks, t_hit *hit, float contrib)
{
	const t_mtl	*mat = hit->object->mat;
	t_fresnel	f;
	t_fvec		col;

	f.refr_index = 1.0f;
	if (hit->inside_ri == 1.0f)
		f.refr_index = mat->opt_dens;
	f.refl_ratio = reflect_amount(hit->inside_ri, f.refr_index, hit);
	col = (t_fvec){};
	if (is_flag(mat, DISSOLVED | TRANSPARENT))
		col += transmit_ray(scene, hit, contrib, f);
	if (f.refl_ratio * contrib > CONTRIB_CUTOFF)
	{
		if (f.refl_ratio == 1.0f)
			contrib -= g_refl_cost;
		col += f.refl_ratio * reflect_ray(scene, hit, f.refl_ratio * contrib) * ks;
	}
	return (col);
}
