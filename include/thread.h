/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 14:40:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/24 17:30:01 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <minirt.h>

//	create_work.c
bool	create_work(t_minirt *data);

//	create_rays.c
bool	create_rays(t_minirt *data, t_jobs *job);

//	work.c
void	*work(void *param);

//	work_utils.c
void	wait_for_new_job(t_minirt *data);
bool	keep_working(t_threading *thread);
void	quit_working(t_minirt *data);

//	reset_work.c
void	clean_rays(t_ray **rays);
void	wipe_image(t_minirt *data);
void	clear_job_lst(t_minirt *data);
bool	reset_work(t_minirt *data);

//	threads.c
bool	init_work_threads(t_minirt *data);
void	join_threads(t_minirt *data);

#endif
