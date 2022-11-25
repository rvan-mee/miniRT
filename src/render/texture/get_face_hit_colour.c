/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_face_hit_colour.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 12:31:29 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/25 21:15:25 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>
#include <ft_math.h>

static t_rgba	get_texture_colour_face(t_hit *hit, t_mtl *mtl, t_face *f)
{
	const t_fvec	uvec = {f->uvw[0].u, f->uvw[1].u, f->uvw[2].u, 0.0f};
	const t_fvec	vvec = {f->uvw[0].v, f->uvw[1].v, f->uvw[2].v, 0.0f};
	const t_fvec	bary = {hit->u, hit->v, 1.0f - hit->u - hit->v, 0.0f};
	const float		u = dot_product(uvec, bary);
	const float		v = dot_product(vvec, bary);

	return (get_uv_colour(&mtl->map_Kd, u, v));
	// t_rgba	rgb;
	// (void)f;
	// (void)mtl;
	// rgb.a = 0xFF;
	// rgb.r = hit->u * 255;
	// rgb.g = hit->v * 255;
	// rgb.b = (1 - hit->v - hit->u) * 255;
	// return (rgb);
}

t_rgba	get_face_hit_colour(t_object *object, t_hit *hit)
{
	if (object->has_mat && object->mat->is_enabled.map_Kd \
		&& object->face.has_texture)
		return (get_texture_colour_face(hit, object->mat, &object->face));
	return (object->colour);
}
