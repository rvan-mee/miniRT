/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_internal.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:55:07 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 17:55:07 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct s_printf_opts
{
	bool	pound;
	bool	zero;
	bool	left;
	bool	space;
	bool	sign;
	int32_t	minwidth;
	int32_t	precision;
}		t_opts;

t_opts		parse_options(const char **str, va_list *args);
void		parse_flags(const char **str, t_opts *opts);

/*
 * ===== CONVERSIONS =====
 */
/**
 * %c
 */
int32_t		printchar(char c, t_opts opts);
/**
 * %%
 *
 * Uses printchar but sets minwidth to 0
 */
int32_t		printpercent(t_opts opts);
/**
 * %s
 */
int32_t		printstr(const char *str, t_opts opts);
/**
 * %diu
 */
int32_t		printnbr(int64_t n, t_opts opts);
/**
 * %xX
 *
 * This function is also used by printptr (%p).
 * @param cap Should the hex value be capitalized?
 * @param pointer Are we dealing with a pointer?
 * The pointer parameter is necessary because pointers always print 0x (even 0)
 */
int32_t		printhex(uint64_t n, t_opts opts, bool cap, bool pointer);
/**
 * %p
 */
int32_t		printptr(void *p, t_opts opts);

/*
 * =======================
 */

/**
 * Return the absolute value of nbr, as an unsigned long
 */
uint64_t	to_uns(int64_t nbr);

/**
 * Return the amount of characters needed to display number nbr in base base
 */
int32_t		length_in_base(uint64_t nbr, uint8_t base, int32_t precision);

/**
 * Write number nbr into the first length characters of str
 * converted to base base
 */
void		write_number(char *s, uint64_t nbr, uint8_t base, uint32_t length);
void		printf_pad(t_opts opts, int count);

#endif //FT_PRINTF_INTERNAL_H
