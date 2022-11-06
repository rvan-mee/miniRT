/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 20:00:36 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 21:04:54 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

float	intersect(const t_object *object, const t_ray *ray)
{
	static t_intersectfun	intersect_functions[] = {\
        [PLANE] = intersect_plane, \
        [CYLINDER] = intersect_cylinder, \
        [SPHERE] = intersect_sphere, \
        [TRIANGLE] = intersect_triangle, \
		[FACE] = intersect_face
	};

	return (intersect_functions[object->type](object, ray, hit));
}
