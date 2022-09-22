/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quadratic.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 19:27:47 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/22 15:55:14 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <ft_math.h>
#include <stdbool.h>

bool	solve_quadratic(t_quadratic *quadratic, float t[2])
{
	float	discriminant;
	float	a;
	float	b;
	float	c;

	a = quadratic->a;
	b = quadratic->b;
	c = quadratic->c;
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0.0)
		return (false);
	discriminant = sqrtf(discriminant);
	a = 1.0 / (2.0 * a);
	t[0] = (-b + discriminant) * a;
	t[1] = (-b - discriminant) * a;
	return (true);
}
