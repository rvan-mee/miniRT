/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nbr_to_str_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:55:07 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 17:55:07 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#define BASE_CHARS "0123456789abcdef"

uint64_t	to_uns(int64_t nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	else
		return (nbr);
}

int32_t	length_in_base(uint64_t nbr, uint8_t base, int32_t precision)
{
	int32_t	n;

	if (nbr == 0)
		return (precision != 0);
	n = 0;
	while (nbr != 0)
	{
		nbr /= base;
		++n;
	}
	return (n);
}

void	write_number(char *str, uint64_t nbr, uint8_t base, uint32_t length)
{
	uint8_t	base_index;

	while (length-- > 0)
	{
		base_index = nbr % base;
		str[length] = BASE_CHARS[base_index];
		nbr /= base;
	}
}
