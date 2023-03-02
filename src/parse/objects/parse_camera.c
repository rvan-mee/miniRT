/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:18:22 by lsinke        #+#    #+#                 */
/*   Updated: 2022/11/07 21:08:22 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>
#include <math.h>
#include <ft_math.h>

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

/**
 * Pre-calculate stuff we need to cast camera rays efficiently.
 *
 * u and y are the camera x and y axis in world space
 *
 * I'd add a link to the explanation here but norminette :^)
 */
void	calc_ray_info(t_camera *cam, float w, float h)
{
	const t_fvec	up = {0, 1, 0};
	const float		ws_ratio = w / 2.f / tanf(cam->fov / 2.f);

	cam->u = normalize_vector(cross_product(up, cam->orientation));
	cam->v = normalize_vector(cross_product(cam->orientation, cam->u));
	cam->proj_vec = (t_fvec){};
	cam->proj_vec += -w / 2.f * cam->u;
	cam->proj_vec += h / 2.0f * cam->v;
	cam->proj_vec += ws_ratio * cam->orientation;
}

t_parse_error	parse_camera(char **linep, t_object *object, t_conf_data *conf)
{
	char	*line;

	(void) conf;
	line = *linep;
	if (!parse_vector(&line, &object->coords, false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &object->camera.orientation, true)
		|| !ft_isspace(*line))
		return (VECTOR);
	if (!parse_fov(&line, &object->camera.fov))
		return (FOV);
	calc_ray_info(&object->camera, WIDTH, HEIGHT);
	*linep = line;
	return (SUCCESS);
}
