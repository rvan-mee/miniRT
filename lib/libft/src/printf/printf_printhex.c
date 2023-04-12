/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_printhex.c                                  :+:    :+:            */
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

static void	add_alt(char *str)
{
	str[0] = '0';
	str[1] = 'x';
}

static char	*ul_to_hex(uint64_t nbr, t_opts opts, int32_t *num_length)
{
	char	*str;

	*num_length = length_in_base(nbr, 16, opts.precision);
	*num_length = ft_max(opts.precision, *num_length);
	if (opts.pound)
		*num_length += 2;
	if (opts.precision >= 0 && opts.zero)
		opts.zero = false;
	if (opts.zero)
		*num_length = ft_max(opts.minwidth, *num_length);
	str = malloc((*num_length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[*num_length] = '\0';
	write_number(str, nbr, 16, *num_length);
	return (str);
}

int32_t	printhex(uint64_t n, t_opts opts, bool capitalize, bool pointer)
{
	char	*nbr_str;
	int32_t	length;

	if (n == 0 && !pointer)
		opts.pound = false;
	nbr_str = ul_to_hex(n, opts, &length);
	if (!nbr_str)
		return (0);
	if (opts.pound)
		add_alt(nbr_str);
	if (capitalize)
		ft_strtoupper(nbr_str);
	if (opts.zero)
		opts.zero = false;
	if (!opts.left)
		printf_pad(opts, opts.minwidth - length);
	write(STDOUT_FILENO, nbr_str, length);
	if (opts.left)
		printf_pad(opts, opts.minwidth - length);
	free(nbr_str);
	return (ft_max(length, opts.minwidth));
}

int32_t	printptr(void *p, t_opts opts)
{
	opts.pound = true;
	return (printhex((uint64_t) p, opts, false, true));
}
