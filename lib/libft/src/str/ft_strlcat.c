/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstlen)
{
	size_t	len_d;
	size_t	len_s;
	size_t	off;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (dstlen == 0)
		return (len_s);
	if (dstlen <= len_d)
		return (len_s + dstlen);
	off = len_d;
	while (*src && dstlen - off - 1 > 0)
	{
		dst[off] = *src;
		++off;
		++src;
	}
	dst[off] = '\0';
	return (len_s + len_d);
}
