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

static float	get_transmittance(t_mtl *mat)
{
	if (is_flag(mat, DISSOLVED))
		return (1.0f - mat->transp_d);
	else if (is_flag(mat, TRANSPARENT))
		return (mat->transp_tr);
	return (0.0f);
}

static
t_fvec	no_refract(t_scene *scene, t_hit *hit, uint8_t depth, float transm)
{
	t_mtl	*mat;
	t_hit	r_hit;
	t_fvec	colour;

	r_hit.ray = get_biased_ray(hit->hit, hit->ray.direction, hit->normal);
	if (!trace(scene, &r_hit.ray, &r_hit))
		return ((t_fvec){});
	colour = shade(scene, &r_hit, depth) * transm;
	mat = hit->object->mat;
	if (is_flag(mat, TRANSMISSION_FILTER))
		colour *= exp_fvec(-mat->tra_filter);
	return (colour);
}

static
t_fvec	transmit_ray(t_scene *scene, t_hit *hit, uint8_t depth, float ri_2)
{
	const float	transmittance = get_transmittance(hit->object->mat);
	t_hit		r_hit;
	t_fvec		r_dir;
	t_fvec		colour;

	if (transmittance <= 0)
		return ((t_fvec){});
	if (hit->object->mat->illum == 4)
		return (no_refract(scene, hit, depth, transmittance));
	r_dir = refract(hit->ray.direction, hit->normal, hit->refl, ri_2);
	r_hit.ray = get_biased_ray(hit->hit, r_dir, hit->normal);
	if (!trace(scene, &r_hit.ray, &r_hit))
		return ((t_fvec){});
	colour = shade(scene, &r_hit, depth + 1) * transmittance;
	if (is_flag(hit->object->mat, TRANSMISSION_FILTER))
		colour *= exp_fvec(-hit->object->mat->tra_filter * r_hit.distance);
	return (colour);
}

t_fvec	fresnel(t_scene *scene, t_fvec ks, t_hit *hit, uint8_t depth)
{
	t_mtl	*mat;
	float	ri_2;
	float	refl;
	t_fvec	col;

	mat = hit->object->mat;
	if (hit->refl != 1.0f)
		ri_2 = 1.0f;
	else
		ri_2 = mat->opt_dens;
	refl = reflect_amount(hit->refl, ri_2, hit);
	col = (t_fvec){};
	if (is_flag(mat, DISSOLVED | TRANSPARENT))
		col += (1.0f - refl) * transmit_ray(scene, hit, depth, ri_2);
	col += refl * reflect_ray(scene, hit, depth) * ks;
	return (col);
}
