/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_printchar.c                                 :+:    :+:            */
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

int32_t	printchar(char c, t_opts opts)
{
	if (!opts.left)
		printf_pad(opts, opts.minwidth - 1);
	ft_putchar_fd(c, STDOUT_FILENO);
	if (opts.left)
		printf_pad(opts, opts.minwidth - 1);
	return (ft_max(1, opts.minwidth));
}

int32_t	printpercent(t_opts opts)
{
	return (printchar('%', opts));
}
