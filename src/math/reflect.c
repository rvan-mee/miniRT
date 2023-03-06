/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 19:41:46 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/06 19:41:46 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_math.h>

t_fvec	reflect(t_fvec in, t_fvec normal)
{
	t_fvec	out;

	out = in - 2 * dot_product(normal, in) * normal;
	return (normalize_vector(out));
}
