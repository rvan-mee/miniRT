/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:54:09 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 19:25:59 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <miniRT.h>

bool	parse_config_file(int32_t argc, char *argv[], t_scene *scene);
bool	parse_scene(int32_t fd, t_scene *dst);
bool	parse_object(char *line, t_object *object);

#endif
