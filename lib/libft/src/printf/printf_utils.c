/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:55:07 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 17:55:07 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_internal.h>
#include <libft.h>
#include <unistd.h>

/**
 * This is just as fast for a count of 1 or 2.
 * The fast way is nearly constant. This way gets way slower for bigger counts.
 *
 * For count = 512 this way takes 330 cycles, the other takes 4.
 * I just kept this so I can work around failed mallocs (lol)
 */
static void	printf_pad_slow(char c, int count)
{
	while (count-- > 0)
		ft_putchar_fd(c, STDOUT_FILENO);
}

void	printf_pad(t_opts opts, int count)
{
	char	*s;
	char	c;

	if (count <= 0)
		return ;
	c = ' ';
	if (opts.zero && !opts.left)
		c = '0';
	s = malloc(count);
	if (!s)
	{
		printf_pad_slow(c, count);
		return ;
	}
	ft_memset(s, c, count);
	write(STDOUT_FILENO, s, count);
	free(s);
}
