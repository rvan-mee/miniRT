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

static t_fvec	rotate(t_fvec old_rot, t_fvec axis, float angle)
{
	t_fvec	new_rotation;

	if (angle == 0)
		return (old_rot);
	new_rotation = old_rot * cosf(angle);
	new_rotation += cross_product(axis, old_rot) * sinf(angle);
	new_rotation += axis * dot_product(axis, old_rot) * (1 - cosf(angle));
	return (new_rotation);
}

/**
 * Pre-calculate stuff we need to cast camera rays efficiently.
 *
 * u and y are the camera x and y axis in world space
 *
 * I'd add a link to the explanation here but norminette :^)
 */
void	calc_ray_info(t_camera *cam, size_t w, size_t h)
{
	const float		dz = ((float) w / 2.f) / tanf(cam->fov / 2.f);
	const t_fvec	global_up = {0, 1, 0};

	cam->rotated = rotate(cam->orientation, global_up, cam->rotation[0]);
	cam->rotated = normalize_vector(cam->rotated);
	cam->u = normalize_vector(cross_product(global_up, cam->rotated));
	cam->rotated = rotate(cam->rotated, cam->u, cam->rotation[1]);
	cam->rotated = normalize_vector(cam->rotated);
	cam->v = normalize_vector(cross_product(cam->rotated, cam->u));
	cam->proj_vec = (t_fvec){};
	cam->proj_vec += (float) w / -2.0f * cam->u;
	cam->proj_vec += (float) h / 2.0f * cam->v;
	cam->proj_vec += dz * cam->rotated;
}

t_parse_err	parse_camera(char **linep, t_object *object, t_conf_data *conf)
{
	t_camera	*cam;
	char		*line;

	(void) conf;
	cam = &object->camera;
	line = *linep;
	if (!parse_vector(&line, &object->coords, false)
		|| !ft_isspace(*line))
		return (COORD);
	if (!parse_vector(&line, &cam->orientation, true)
		|| !ft_isspace(*line))
		return (VECTOR);
	if (!parse_fov(&line, &cam->fov))
		return (FOV);
	cam->exposure = conf->exposure;
	*linep = line;
	return (SUCCESS);
}
