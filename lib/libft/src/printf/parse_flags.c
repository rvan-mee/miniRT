/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_flags.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:55:07 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 17:55:07 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_internal.h>

static void	set_zero(t_opts *opts)
{
	if (!opts->left)
		opts->zero = true;
}

static void	set_left(t_opts *opts)
{
	opts->left = true;
	opts->zero = false;
}

static void	set_space(t_opts *opts)
{
	if (!opts->sign)
		opts->space = true;
}

static void	set_sign(t_opts *opts)
{
	opts->sign = true;
	opts->space = false;
}

void	parse_flags(const char **str, t_opts *opts)
{
	const char	*s;

	s = *str;
	while (*s)
	{
		if (*s == '#')
			opts->pound = true;
		else if (*s == '0')
			set_zero(opts);
		else if (*s == '-')
			set_left(opts);
		else if (*s == ' ')
			set_space(opts);
		else if (*s == '+')
			set_sign(opts);
		else
			break ;
		++s;
	}
	*str = s;
}
