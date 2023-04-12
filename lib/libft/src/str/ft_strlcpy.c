/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstlen)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dstlen)
		ft_memcpy(dst, src, srclen + 1);
	else if (dstlen != 0)
	{
		ft_memcpy(dst, src, dstlen - 1);
		dst[dstlen - 1] = '\0';
	}
	return (srclen);
}
