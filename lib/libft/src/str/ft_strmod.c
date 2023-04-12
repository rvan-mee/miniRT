/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmod.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_strtoupper(char *str)
{
	while (*str)
	{
		*str = (char) ft_toupper(*str);
		++str;
	}
}

void	ft_strtolower(char *str)
{
	while (*str)
	{
		*str = (char) ft_tolower(*str);
		++str;
	}
}
