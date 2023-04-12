/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hextoui.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:31:11 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/21 13:31:11 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#define BASE_CHARS "0123456789ABCDEF"

static int	indexof(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

unsigned int	ft_hextoui(const char *str)
{
	unsigned int	val;
	const char		*s;
	int				idx;

	s = ft_strchr(str, 'x');
	if (s)
		++s;
	else
		s = str;
	val = 0;
	while (*s)
	{
		idx = indexof(BASE_CHARS, (char) ft_toupper((char) *s));
		if (idx < 0)
			break ;
		val *= 16;
		val += idx;
		++s;
	}
	return (val);
}
