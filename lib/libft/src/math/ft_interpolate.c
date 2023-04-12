/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_interpolate.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 19:50:06 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/28 19:50:06 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_interpolate_i(int a, int b, double p)
{
	return ((int)(a + (b - a) * p));
}

double	ft_interpolate_d(double a, double b, double p)
{
	return (a + (b - a) * p);
}
