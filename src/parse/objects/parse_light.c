/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:18:23 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 21:03:51 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_light(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;

	line = *linep;
	if (!parse_vector(&line, &object->coords, false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_float(&line, &object->light.brightness, 0.0f, 1.0f)
		|| !ft_isspace(*line))
		return (BRIGHT);
	if (!parse_rgb(&line, &object->colour))
		return (COLOUR);
	if (!dynarr_addone(&conf->lights, &object->light))
		return (DYNARR);
	*linep = line;
	return (SUCCESS);
}
