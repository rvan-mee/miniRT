/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:55:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/13 19:57:59 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parse.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define ERR_EXTENSION	"Error\nWrong file extension: `%s'\n"
#define ERR_OPEN		"Error\nFile failed to open: %s: %s\n"
#define ERR_USAGE		"Error\nPlease use ./miniRT [config file]\n"

static bool	check_extension(const char *config_file)
{
	const size_t	len = ft_strlen(config_file);

	if (ft_strncmp(&config_file[len - 3], ".rt", 4) == 0)
		return (true);
	dprintf(STDERR_FILENO, ERR_EXTENSION, config_file);
	return (false);
}

static bool	open_config_file(const char *config_file, int32_t *fd)
{
	*fd = open(config_file, O_RDONLY);
	if (*fd != -1)
		return (true);
	dprintf(STDERR_FILENO, ERR_OPEN, config_file, strerror(errno));
	return (false);
}

bool	parse_config_file(int32_t argc, char *argv[], t_scene *scene)
{
	int32_t	fd;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, ERR_USAGE);
		return (false);
	}
	if (!check_extension(argv[1]) || !open_config_file(argv[1], &fd))
		return (false);
	if (!parse_scene(fd, scene))
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
