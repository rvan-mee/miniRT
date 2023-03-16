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

static t_fvec	refract(t_hit *hit, float mu)
{
	const t_fvec	in = hit->ray.direction;
	const t_fvec	norm = hit->normal;
	const float		cos_t = -(dot_product(in, norm));
	t_fvec			t;

	t = mu * in;
	t += norm * (mu * cos_t - sqrtf(1 - mu * mu * (1 - cos_t * cos_t)));
	return (normalize_vector(t));
}

static t_fvec	transmit_ray(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth, float ri_2)
{
	t_hit	rhit;
	float	transmittance;
	float	bias;

	transmittance = 0;
	if (object->mat->is_enabled.transp_d)
		transmittance = 1.0f - object->mat->transp_d;
	else if (object->mat->is_enabled.transp_tr)
		transmittance = object->mat->transp_tr;
	if (transmittance > 0)
	{
		rhit.ray.direction = refract(hit, hit->refl / ri_2);
		bias = get_ray_bias(hit->normal, rhit.ray.direction);
		rhit.ray.origin = hit->hit + rhit.ray.direction * bias;
		rhit.refl = object->mat->opt_dens;
		if (!intersect_bvh(&scene->bvh, &rhit.ray, &rhit))
			return ((t_fvec){});
		rhit.hit = rhit.ray.origin + rhit.ray.direction * rhit.distance;
		calculate_normal(&rhit);
		// todo: Add transmission filter
		return (get_hit_colour(scene, rhit.object, &rhit, depth + 1) * transmittance);
	}
	return (object->mat->diffuse);
}

static t_fvec	reflect_ray(t_scene *scene, t_hit *hit, uint8_t depth)
{
	t_hit	r_hit;
	t_fvec	colour;
	float	bias;

	colour = (t_fvec) {};
	r_hit.ray.direction = reflect(hit->ray.direction, hit->normal);
	bias = get_ray_bias(hit->normal, r_hit.ray.direction);
	r_hit.ray.origin = hit->hit + r_hit.ray.direction * bias;
	if (!intersect_bvh(&scene->bvh, &r_hit.ray, &r_hit))
		return (colour);
	r_hit.hit = r_hit.ray.origin + r_hit.ray.direction * r_hit.distance;
	calculate_normal(&r_hit);
	colour = get_hit_colour(scene, r_hit.object, &r_hit, depth + 1);
	return (colour);
}

t_fvec	fresnel(t_scene *scene, t_object *object, t_hit *hit, uint8_t depth)
{
	const t_mtl	*mat = object->mat;
	float		ri_2;
	float		refl;
	t_fvec		col;

	//printf("hit->refl == %f\n", hit->refl);
	if (hit->refl != 1.0f)
		ri_2 = 1.0f;
	else
		ri_2 = mat->opt_dens;
	refl = reflect_amount(hit->refl, ri_2, hit);
	col = (1.0f - refl) * transmit_ray(scene, object, hit, depth, ri_2);
	if (depth < MAX_REFLECTION_DEPTH)
		col += refl * reflect_ray(scene, hit, depth);
	return (col);
}
