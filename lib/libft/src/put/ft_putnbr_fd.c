/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	putnbr_rec(long n, int fd)
{
	if (n == 0)
		return ;
	putnbr_rec(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	l;

	l = n;
	if (l == 0)
		ft_putchar_fd('0', fd);
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l *= -1;
	}
	putnbr_rec(l, fd);
}
