/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:55:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/17 14:14:46 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <unistd.h>
#include <stdio.h>

#define ERR_USAGE		"Error\nPlease use ./miniRT [config file]\n"

bool	parse_config_file(int32_t argc, char *argv[], t_scene *scene)
{
	int32_t	fd;
	bool	success;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, ERR_USAGE);
		return (false);
	}
	if (!check_extension(argv[1], "obj") || !open_file(argv[1], &fd))
		return (false);
	success = parse_scene(fd, scene);
	close(fd);
	if (!success)
		return (false);
	normalize(scene);
	return (true);
}
