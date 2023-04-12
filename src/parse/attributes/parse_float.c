/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_float.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 20:23:50 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/22 18:52:11 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

bool	parse_float(char **linep, float *dst, float min, float max)
{
	char	*end;

	*dst = strtof(*linep, &end);
	if (*linep == end || !ft_isdigit(end[-1]))
		return (false);
	*linep = end;
	if (min == max)
		return (true);
	return (*dst >= min && *dst <= max);
}
