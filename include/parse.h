/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:54:09 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/14 17:25:29 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <minirt.h>

typedef enum e_parse_error {
	SUCCESS,
	OBJECT,
	COORD,
	VECTOR,
	COLOUR,
	FORMAT,
	LRATIO,
	FOV,
	BRIGHT,
	DIAMETER,
	OBJ_HEIGHT
}	t_parse_error;

bool			parse_config_file(int32_t argc, char *argv[], t_scene *scene);
bool			parse_scene(int32_t fd, t_scene *dst);
bool			parse_object(char *line, t_object *object);
t_parse_error	parse_ambient(char **linep, t_object *object);
t_parse_error	parse_camera(char **linep, t_object *object);
t_parse_error	parse_light(char **linep, t_object *object);
t_parse_error	parse_sphere(char **linep, t_object *object);
t_parse_error	parse_plane(char **linep, t_object *object);
t_parse_error	parse_cylinder(char **linep, t_object *object);
bool			parse_rgb(char **linep, t_rgba *colour);
bool			parse_line_error(const char *line, t_parse_error err);
void			skip_spaces(char **linep);
bool			parse_vector(char **linep, t_fvec *vector, bool normalized);
bool			parse_float(char **linep, float *dst, float min, float max);
void			normalize(t_scene *scene);
void			normalize_coords(t_scene *scene);

#endif
