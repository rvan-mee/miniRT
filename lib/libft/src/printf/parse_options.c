/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_options.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:55:07 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 17:55:07 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_internal.h>
#include <libft.h>

static void	initialize_options(t_opts *opts)
{
	opts->pound = false;
	opts->zero = false;
	opts->left = false;
	opts->space = false;
	opts->sign = false;
	opts->minwidth = 0;
	opts->precision = -1;
}

static int32_t	parse_number(const char **str, va_list *args)
{
	const char	*s;
	int32_t		retval;

	s = *str;
	if (*s == '*')
	{
		*str = ++s;
		return (va_arg(*args, int));
	}
	retval = 0;
	while (ft_isdigit(*s))
	{
		retval *= 10;
		retval += *s - '0';
		++s;
	}
	*str = s;
	return (retval);
}

t_opts	parse_options(const char **str, va_list *args)
{
	t_opts		opts;

	initialize_options(&opts);
	parse_flags(str, &opts);
	if (ft_isdigit(**str) || **str == '*')
	{
		opts.minwidth = parse_number(str, args);
		if (opts.minwidth < 0)
		{
			opts.minwidth *= -1;
			opts.left = true;
			opts.zero = false;
		}
	}
	if (**str == '.')
	{
		++(*str);
		opts.precision = parse_number(str, args);
	}
	return (opts);
}
