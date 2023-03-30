/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   headless.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 02:32:56 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/30 02:32:56 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADLESS_H
# define HEADLESS_H
# include <stdint.h>

typedef struct s_fakeimg {
	uint32_t	width;
	uint32_t	height;
	uint8_t*	pixels;
}	t_fakeimg;

#endif //HEADLESS_H
