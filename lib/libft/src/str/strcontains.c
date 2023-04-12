/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strcontains.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: user <user@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:33:17 by user          #+#    #+#                 */
/*   Updated: 2022/06/22 13:33:17 by user          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	strcontains(const char *str, char c)
{
	while (*str)
		if (c == *str++)
			return (true);
	return (false);
}
