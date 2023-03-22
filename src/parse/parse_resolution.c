/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_resolution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:34:38 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/22 16:34:38 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <libft.h>

bool	parse_resolution(t_minirt *data, char *str)
{
	int32_t	val;

	val = ft_atoi(str);
	if (val <= 0)
		return (false);
	data->width = val;
	while (ft_isdigit(*str))
		++str;
	if (*str != 'x')
		return (false);
	++str;
	val = ft_atoi(str);
	if (val <= 0)
		return (false);
	data->height = val;
	while (ft_isdigit(*str))
		++str;
	return (*str == '\0');
}
