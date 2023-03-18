/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_usemesh.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 22:19:26 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/18 22:19:26 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse_obj.h>
#include <libft.h>
#include <ft_math.h>
#include <math.h>

static bool	get_name(char **linep, char **dst)
{
	char	*line;

	skip_spaces(linep);
	line = *linep;
	while (*line && !ft_isspace(*line))
		++line;
	*dst = ft_substr(*linep, 0, line - *linep);
	*linep = line;
	return (*dst != NULL);
}

t_parse_err	parse_params(char **linep, t_meshparams *dst)
{
	if (!get_name(linep, &dst->name))
		return (ALLOC);
	skip_spaces(linep);
	if (!parse_vector(linep, &dst->coords, false))
		return (free(dst->name), COORD);
	skip_spaces(linep);
	if (!parse_vector(linep, &dst->w, true))
		return (free(dst->name), VECTOR);
	skip_spaces(linep);
	if (!parse_vector(linep, &dst->v, true))
		return (free(dst->name), VECTOR);
	if (fabsf(dot_product(dst->w, dst->v)) > FLOAT_EPSILON)
		return (free(dst->name), VECTOR);
	dst->u = normalize_vector(cross_product(dst->v, dst->w));
	skip_spaces(linep);
	if (!parse_float(linep, &dst->scale, 0, 0))
		return (free(dst->name), INV_SCALE);
	return (SUCCESS);
}

t_parse_err	parse_usemesh(char **linep, t_object *object, t_conf_data *conf)
{
	t_meshparams	params;
	t_parse_err		err;

	(void) object;
	err = parse_params(linep, &params);
	if (err != SUCCESS)
		return (err);
	return (add_mesh(params, conf));
}
