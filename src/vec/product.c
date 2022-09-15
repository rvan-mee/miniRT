/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   product.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:38:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/15 20:38:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	dot_product(t_fvec a, t_fvec b)
{
	const t_fvec	product = a * b;

	return (product[X] + product[Y] + product[Z]);
}

t_fvec	cross_product(t_fvec a, t_fvec b)
{
	t_fvec	result;

	result[X] = a[Y] * b[Z] - b[Y] * a[Z];
	result[Y] = a[Z] * b[X] - b[Z] * a[X];
	result[Z] = a[X] * b[Y] - b[X] * a[Y];
	return (result);
}
