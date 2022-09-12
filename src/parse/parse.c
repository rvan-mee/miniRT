/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 17:55:13 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 20:58:32 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <libft.h>
#include <parse.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/errno.h>

static bool	check_extention(char *config_file)
{
	int32_t	len;

	len = ft_strlen(config_file);
	if (ft_strncmp(&config_file[len - 3], ".rt", 4) != 0)
	{
		write(STDERR_FILENO, "Error\nWrong file extention\n", 28);
		return (false);
	}
	return (true);
}

static bool	open_config_file(char *config_file, int32_t *fd)
{
	*fd = open(config_file, R_OK);
	if (*fd == -1)
	{
		write(STDERR_FILENO, "Error\n", 7);
		perror(errno);
		return (false);
	}
	return (true);
}

bool	parse_config_file(int32_t argc, char *argv[], t_scene *scene)
{
	int32_t	fd;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error\nPlease use ./miniRT [config file]\n", 41);
		return (false);
	}
	if (!check_extention(argv[1]) || !open_config_file(argv[1], &fd))
		return (false);
	if (set_objects(fd, scene))
	{
		close (fd);
		return (false);
	}
	close(fd);
	return (true);
}
