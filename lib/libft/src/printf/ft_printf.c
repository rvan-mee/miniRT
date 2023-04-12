/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:55:07 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 17:55:07 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_internal.h>
#include <unistd.h>

int32_t	print_type(char c, t_opts options, va_list *args)
{
	if (c == 'c')
		return (printchar((char) va_arg(*args, int), options));
	if (c == 's')
		return (printstr(va_arg(*args, char *), options));
	if (c == 'p')
		return (printptr(va_arg(*args, void *), options));
	if (c == 'd' || c == 'i')
		return (printnbr(va_arg(*args, int), options));
	if (c == 'u')
		return (printnbr(va_arg(*args, unsigned int), options));
	if (c == 'x')
		return (printhex(va_arg(*args, unsigned int), options, false, false));
	if (c == 'X')
		return (printhex(va_arg(*args, unsigned int), options, true, false));
	if (c == '%')
		return (printpercent(options));
	return (0);
}

int32_t	insert_conversion(const char **str, va_list *args)
{
	t_opts	options;
	int32_t	printed;

	options = parse_options(str, args);
	printed = print_type(**str, options, args);
	(*str)++;
	return (printed);
}

/**
 * Print characters from str, until either a '%' or a '\0' is reached
 * This function increments the pointer in str to the '%' or '\0'
 * @return The amount of characters were printed.
 */
int32_t	print_until_percent(const char **str)
{
	const char	*s;
	int32_t		count;

	s = *str;
	count = 0;
	while (s[count] && s[count] != '%')
		++count;
	write(STDOUT_FILENO, s, count);
	*str += count;
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int32_t	printed;

	printed = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str != '%')
			printed += print_until_percent(&str);
		else
		{
			++str;
			printed += insert_conversion(&str, &args);
		}
	}
	va_end(args);
	return (printed);
}
