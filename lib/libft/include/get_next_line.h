/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 12:59:16 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/20 12:59:16 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 0x100000
# endif

# include <stdlib.h>

typedef enum e_gnl_status {
	GNL_CONTINUE,
	GNL_DONE,
	GNL_FINISHED,
	GNL_ERROR,
	GNL_ERROR_FILE
}	t_gnl_err;

typedef struct s_filebuf {
	int		fd;
	char	buf[BUFFER_SIZE];
	size_t	start;
	size_t	len;
}	t_filebuf;

size_t	get_next_line(int fd, char **dst);
char	*get_next_line_dumb(int fd);

static inline
void	cleanup_gnl(void)
{
	get_next_line(-1, NULL);
}

#endif