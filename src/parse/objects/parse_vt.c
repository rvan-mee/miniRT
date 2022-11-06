/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vt.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 15:27:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/06 19:36:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_vt(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;
	float	u;
	float	v;

	line = *linep;
	skip_spaces(&line);
	if (!ft_isdigit(*line))
		return (COORD);
	u = ft_strtof(line, &line);
	if (u < 0.0f || u > 1.0f)
		return (COORD);
	skip_spaces(&line);
	v = 0;
	if (ft_isdigit(*line))
	{
		v = ft_strtof(line, &line);
		if (v < 0.0f || v > 1.0f)
			return (COORD);
	}
	object->vertex_texture.uv.u = u;
	object->vertex_texture.uv.v = v;
	if (!dynarr_addone(&conf->vertex_textures, &object->vertex_texture))
		return (DYNARR);
	*linep = line;
	return (SUCCESS);
}
