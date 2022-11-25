/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_triangle_hit_colour.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 18:36:03 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:41:41 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <texture.h>

t_rgba	get_tri_hit_colour(t_object *object, t_hit *hit)
{
	(void) hit;
	return (object->colour);
}
