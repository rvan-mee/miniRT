/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_plane_hit_colour.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 12:30:18 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:41:30 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_rgba	get_plane_hit_colour(t_object *object, t_hit *hit)
{
	(void) hit;
	return (object->colour);
}
