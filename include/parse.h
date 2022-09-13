/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:54:09 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/13 14:53:27 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <miniRT.h>

typedef enum e_parse_error {
	OBJECT,
	COORD,
	VECTOR,
	COLOUR,
	FORMAT,
	LRATIO
}	t_parse_error;

bool	parse_config_file(int32_t argc, char *argv[], t_scene *scene);
bool	parse_scene(int32_t fd, t_scene *dst);
bool	parse_object(char *line, t_object *object);
bool	set_objects(int32_t fd, t_scene *scene);
bool	parse_rgb(char *line, t_rgba *colour);
bool	parse_line_error(char *line, t_parse_error err);
bool	parse_vector(char *line, t_fvec *vector, bool normalized);

#endif
