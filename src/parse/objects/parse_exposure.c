/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_exposure.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 16:58:55 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/11 13:37:18 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <float.h>

t_parse_error	parse_exposure(char **linep, t_object *object, t_conf_data *conf)
{
	(void) object;
	if (!parse_float(linep, &conf->exposure, -FLT_MAX, FLT_MAX  -1)) // -FLT_MIN == 0.0 on codam macs??
		return (EXPOS);
	return (SUCCESS);
}
