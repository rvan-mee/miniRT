/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:55:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/11/22 18:57:36 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <unistd.h>
#include <stdio.h>

#define ERR_USAGE		"Error\nPlease use ./miniRT [config file]\n"
#include <time.h>
bool	parse_config_file(int32_t argc, char *argv[], t_scene *scene)
{
	int32_t	fd;
	bool	success;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, ERR_USAGE);
		return (false);
	}
	clock_t start = clock();
	if ((!check_extension(argv[1], ".rt")) || !open_file(argv[1], &fd))
		return (false);
	success = parse_scene(fd, scene);
	close(fd);
	if (!success)
		return (false);
	dprintf(1, "Parsing took %lf!\n", (clock() - start) / (double) CLOCKS_PER_SEC);
	return (true);
}
