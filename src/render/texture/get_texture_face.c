/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_texture_face.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 12:31:29 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/25 21:15:25 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>
#include <ft_math.h>

static void	get_uv(t_hit *hit, float *u, float *v)
{
	const t_face	*f = &hit->object->face;
	const t_fvec	uvec = {f->uvw[0][0], f->uvw[1][0], f->uvw[2][0]};
	const t_fvec	vvec = {f->uvw[0][1], f->uvw[1][1], f->uvw[2][1]};

	*u = dot_product(uvec, hit->bary);
	*v = 1.0f - dot_product(vvec, hit->bary);
}

t_fvec	get_texture_face(t_hit *hit, t_bmp *texture)
{
	float	u;
	float	v;

	if (hit->object->face.has_texture)
		get_uv(hit, &u, &v);
	else
	{
		u = hit->bary[0];
		v = hit->bary[1];
	}
	return (get_uv_colour(texture, u, v));
}
