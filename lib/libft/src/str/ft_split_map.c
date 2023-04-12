/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 18:34:14 by lsinke        #+#    #+#                 */
/*   Updated: 2022/04/20 18:34:14 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	cleanup(void ***trash, void (*del)(void *))
{
	void	**t;

	t = *trash;
	while (*t)
	{
		del(*t);
		++t;
	}
	free(*trash);
	*trash = NULL;
}

static void	**do_map(char **strs, void *(*map)(char *), void (*del)(void *))
{
	void	**ret;
	size_t	n;
	size_t	i;

	n = 0;
	while (strs[n])
		++n;
	ret = ft_calloc(n + 1, sizeof(void *));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ret[i] = map(strs[i]);
		if (!ret[i])
		{
			cleanup(&ret, del);
			return (NULL);
		}
		++i;
	}
	return (ret);
}

void	**ft_split_map(const char *s, char c,
						void *(*map)(char *), void (*del)(void *))
{
	void	**ret;
	char	**strs;

	strs = ft_split(s, c);
	if (!strs)
		return (NULL);
	ret = do_map(strs, map, del);
	cleanup((void ***) &strs, &free);
	return (ret);
}
