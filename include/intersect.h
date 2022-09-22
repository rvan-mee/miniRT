/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 16:29:24 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/22 15:57:55 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include <minirt.h>
# include <math.h>

# define MISS INFINITY

float	intersect_sphere(t_object *obj, t_ray ray);

#endif
