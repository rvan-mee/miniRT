/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:18:22 by lsinke        #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/11/07 21:02:00 by rvan-mee      ########   odam.nl         */
=======
/*   Updated: 2022/11/06 15:34:21 by rvan-mee      ########   odam.nl         */
>>>>>>> v, vt and vn parsing done, face rendering too. check for norm and if everything works properly next up.
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <math.h>

static bool	parse_fov(char **linep, float *dst)
{
	static const float	deg_per_rad = (float)(180.0 / M_PI);
	char				*line;
	int32_t				num;

	line = *linep;
	num = ft_atoi(line);
	if (num <= 0 || num >= 180)
		return (false);
	*dst = (float) num / deg_per_rad;
	skip_spaces(&line);
	if (*line == '+' || *line == '-')
		++line;
	while (*line && ft_isdigit(*line))
		line++;
	*linep = line;
	return (true);
}

t_parse_error	parse_camera(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;

	line = *linep;
	if (!parse_vector(&line, &object->coords, false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &object->camera.orientation, true)
		|| !ft_isspace(*line))
		return (VECTOR);
	if (!parse_fov(&line, &object->camera.fov))
		return (FOV);
	*linep = line;
	return (SUCCESS);
}
