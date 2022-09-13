/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 19:20:49 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 21:02:09 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <parse.h>
#include <libft.h>
#include <unistd.h>

static bool	get_camera(char *line, t_object *object);
static bool	get_light(char *line, t_object *object);
static bool	get_sphere(char *line, t_object *object);
static bool	get_plane(char *line, t_object *object);
static bool	get_cylinder(char *line, t_object *object);

static bool	get_ambient(char *line, t_object *object)
{
	object->type = AMBIENT;
	object->ambient.ratio = ft_strtof(line, &line);
	if (*line != ' ')
	{
		object->type = ERROR;
		return (false);
	}
	return (true);
}

bool	parse_object(char *line, t_object *object)
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (get_ambient(line + 1, object));
	if (ft_strncmp(line, "C", 1) == 0)
		return (get_camera(&line[1], object));
	if (ft_strncmp(line, "L", 1) == 0)
		return (get_light(&line[1], object));
	if (ft_strncmp(line, "sp", 2) == 0)
		return (get_sphere(&line[2], object));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (get_plane(&line[2], object));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (get_cylinder(&line[2], object));
	write(STDERR_FILENO, "Error\nLine `", 13);
	write(STDERR_FILENO, line, ft_strlen(line));
	write(STDERR_FILENO, "' does not contain a valid object\n", 33);
	object->type = ERROR;
	return (false);
}
