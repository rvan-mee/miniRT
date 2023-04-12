/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 11:16:10 by lsinke        #+#    #+#                 */
/*   Updated: 2022/09/30 11:16:10 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>
#include <libft.h>
#include <stdio.h>

int8_t	wrap_strncmp(char **a, char **b)
{
	return (ft_strncmp(*a, *b, SIZE_MAX));
}

int	main(int argc, char **argv)
{
	t_sort	sort = {++argv, sizeof(char *), (t_cmp) wrap_strncmp};

	squicksort(&sort, 0, argc - 2);
	while (*argv)
		printf("%s\n", *argv++);
}