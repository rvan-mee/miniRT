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

bool		parse_config_file(int32_t argc, char *argv[], t_scene *scene);
bool		set_objects(int32_t fd, t_scene *scene);
t_object	parse_object(char *line);

#endif
