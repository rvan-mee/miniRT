/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_exposure.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:58:55 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/08 16:58:55 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <float.h>

t_parse_error	parse_exposure(char **linep, t_object *object, t_conf_data *conf)
{
	(void) object;
	if (!parse_float(linep, &conf->exposure, 0.1f, FLT_MAX))
		return (EXPOS);
	return (SUCCESS);
}
