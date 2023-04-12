/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtof.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 15:36:50 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/12 15:36:50 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#define NUM_LEN		0
#define DEC_IDX		1
#define EXP_LEN		2
#define WHITESPACE	"\t\n\v\f\r "

static const float	g_ten_pows[] = {
	10.0f,
	100.0f,
	1.0e4f,
	1.0e8f,
	1.0e16f,
	1.0e32f
};

static void	get_indices(const char *str, int32_t data[3], char **end)
{
	int32_t	num_len;

	data[DEC_IDX] = -1;
	num_len = 0;
	while (true)
	{
		if (!ft_isdigit(*str))
		{
			if (*str != '.' || data[DEC_IDX] >= 0)
				break ;
			data[DEC_IDX] = num_len;
		}
		++num_len;
		++str;
	}
	if (end != NULL)
		*end = (char *) str;
	if (data[DEC_IDX] < 0)
		data[DEC_IDX] = num_len;
	else
		num_len--;
	if (num_len > 18)
		num_len = 18;
	data[NUM_LEN] = num_len;
	data[EXP_LEN] = data[DEC_IDX] - num_len;
}

static float	get_value(const char *str, int32_t data[3])
{
	int32_t	num_parts[2];
	char	c;

	num_parts[0] = 0;
	num_parts[1] = 0;
	while (data[NUM_LEN] > 9)
	{
		c = *str++;
		if (c == '.')
			c = *str++;
		num_parts[0] = 10 * num_parts[0] + (c - '0');
		--data[NUM_LEN];
	}
	while (data[NUM_LEN] > 0)
	{
		c = *str++;
		if (c == '.')
			c = *str++;
		num_parts[1] = 10 * num_parts[1] + (c - '0');
		--data[NUM_LEN];
	}
	return ((1.0e9f * (float) num_parts[0]) + (float) num_parts[1]);
}

static float	to_float(int32_t data[3], float result)
{
	const float	*pow = g_ten_pows;
	const bool	exp_neg = data[EXP_LEN] < 0;
	float		true_exp;

	true_exp = 1.0f;
	if (exp_neg)
		data[EXP_LEN] *= -1;
	while (data[EXP_LEN] != 0)
	{
		if (data[EXP_LEN] & 1)
			true_exp *= *pow;
		data[EXP_LEN] >>= 1;
		++pow;
	}
	if (exp_neg)
		result /= true_exp;
	else
		result *= true_exp;
	return (result);
}

// 1 bit sign, 8 bits exponent, 23 for value
float	ft_strtof(const char *str, char **end)
{
	bool	negative;
	int32_t	data[3];
	float	result;

	while (*str && ft_strchr(WHITESPACE, *str) != NULL)
		++str;
	negative = (*str == '-');
	if (*str == '-' || *str == '+')
		++str;
	get_indices(str, data, end);
	if (data[NUM_LEN] == 0)
		return (0.0f);
	result = get_value(str, data);
	result = to_float(data, result);
	if (negative)
		return (-result);
	else
		return (result);
}
