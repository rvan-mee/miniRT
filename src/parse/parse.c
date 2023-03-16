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
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>

#define ERR_USAGE	"Error\nPlease use ./miniRT [config file]\n"
#define TIME_MSG1	"Parsing took %"
#define TIME_MSG2	"ms!\n"

static void	print_timer(const uint64_t start)
{
	static const uint64_t	clocks_per_ms = CLOCKS_PER_SEC / 1000;
	const uint64_t			end = clock();

	printf(TIME_MSG1 PRIu64 TIME_MSG2, (end - start) / clocks_per_ms);
}

static bool	alloc_scene(t_scene **dst)
{
	*dst = ft_calloc(1, sizeof(t_scene));
	return (*dst != NULL);
}

bool	parse_config_file(int32_t argc, char *argv[], t_scene **scene)
{
	const uint64_t	start = clock();
	int32_t			fd;
	bool			success;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, ERR_USAGE);
		return (false);
	}
	if (!check_extension(argv[1], ".rt") || !open_file(argv[1], &fd))
		return (false);
	success = alloc_scene(scene) && parse_scene(fd, *scene);
	close(fd);
	if (!success)
		return (false);
	print_timer(start);
	return (true);
}
