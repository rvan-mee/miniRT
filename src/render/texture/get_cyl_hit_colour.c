/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cyl_hit_colour.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 12:30:56 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/23 14:41:47 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_rgba	get_cyl_hit_colour(t_object *object, t_hit *hit)
{
	(void) hit;
	return (object->colour);
}
