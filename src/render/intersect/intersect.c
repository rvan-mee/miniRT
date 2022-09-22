/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 20:00:36 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/21 20:00:36 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

float	intersect(t_object *object, t_ray *ray)
{
	static float	(*intersect_functions[])(t_object *, t_ray *) = {
		[PLANE] = intersect_plane,
		//[CYLINDER] = intersect_cylinder,
		[SPHERE] = intersect_sphere
	};

	return (intersect_functions[object->type](object, ray));
}
