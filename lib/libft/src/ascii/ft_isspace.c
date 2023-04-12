/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 19:55:12 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/14 19:55:12 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#define WHITESPACE	"\t\n\v\f\r "

bool	ft_isspace(int c)
{
	if (c != '\0' && ft_strchr(WHITESPACE, c) != NULL)
		return (true);
	return (false);
}
