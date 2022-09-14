/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 17:12:53 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/14 17:22:37 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

t_parse_error	parse_plane(char **linep, t_object *object)
{
	char	*line;

	line = *linep;
	if (!parse_vector(line, &line, &object->plane.coords, false) \
		|| !is_space(*line))
		return (COORD);
	if (!parse_vector(line, &line, &object->plane.orientation, true) \
		|| !is_space(*line))
		return (VECTOR);
	if (!parse_rgb(line, &line, &object->plane.colour))
		return (COLOUR);
	*linep = line;
	return (SUCCESS);
}
