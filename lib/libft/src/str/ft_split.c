/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/**
 * Returns a pointer to the first character of a word
 */
static char	*find_next_word(const char *str, char c)
{
	char	*p;

	p = ft_strchr(str, c);
	if (p == NULL)
		return (NULL);
	while (*p == c)
		++p;
	if (!*p)
		return (NULL);
	return (p);
}

static size_t	count_words(const char *str, char c)
{
	size_t	n;
	char	*p;

	if (c == '\0')
		return (*str != '\0');
	n = 0;
	p = (char *) str;
	if (*p && *p != c)
		++n;
	while (1)
	{
		p = find_next_word(p, c);
		if (!p)
			return (n);
		++n;
	}
}

static void	cleanup(char ***strs, size_t n)
{
	while (n)
	{
		--n;
		free(*strs[n]);
	}
	free(*strs);
	*strs = NULL;
}

static void	do_splitting(const char *str, char c, char ***strs, size_t n_words)
{
	char	*word;
	char	*wordend;
	size_t	wl;
	size_t	i;

	i = 0;
	word = (char *) str;
	while (i < n_words)
	{
		while (*word == c)
			++word;
		wordend = ft_strchr(word, c);
		if (!wordend)
			wordend = ft_strchr(word, 0);
		wl = wordend - word;
		(*strs)[i] = ft_substr(word, 0, wl);
		if ((*strs)[i] == NULL)
		{
			cleanup(strs, i);
			return ;
		}
		word = wordend;
		++i;
	}
}

char	**ft_split(const char *str, char c)
{
	char	**strs;
	size_t	n_words;

	if (!str)
		return (NULL);
	n_words = count_words(str, c);
	strs = malloc((n_words + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[n_words] = NULL;
	do_splitting(str, c, &strs, n_words);
	return (strs);
}
