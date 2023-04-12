/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	contains(const char *set, char val)
{
	while (*set)
	{
		if (*set == val)
			return (1);
		++set;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char		*ret;
	const char	*end;
	size_t		len;

	if (!str)
		return (NULL);
	while (contains(set, *str))
		++str;
	if (!*str)
		return (ft_strdup(""));
	end = ft_strchr(str, 0) - 1;
	while (contains(set, *end))
		--end;
	len = end - str + 1;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, len + 1);
	return (ret);
}
