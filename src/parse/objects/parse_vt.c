/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vt.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 15:27:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/18 20:55:28 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_error	parse_vt(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;
	float	u;
	float	v;
	float	w;

	line = *linep;
	v = 0;
	w = 0;
	skip_spaces(&line);
	if (!parse_float(&line, &u, 0.0f, 1.0f))
		return (COORD);
	skip_spaces(&line);
	if (ft_isdigit(*line))
	{
		if (!parse_float(&line, &v, 0.0f, 1.0f))
			return (COORD);
		skip_spaces(&line);
		if (ft_isdigit(*line) && !parse_float(&line, &w, 0.0f, 1.0f))
			return (COORD);
	}
	object->vertex_texture.uvw.u = u;
	object->vertex_texture.uvw.v = v;
	object->vertex_texture.uvw.w = w;
	if (!dynarr_addone(&conf->vertex_textures, &object->vertex_texture))
		return (DYNARR);
	*linep = line;
	return (SUCCESS);
}
