/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/11 20:35:51 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/09/12 15:00:37 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

# define WIDTH 1920
# define HEIGHT 1080

void	create_mlx(mlx_t **mlx, mlx_image_t **img);

#endif
