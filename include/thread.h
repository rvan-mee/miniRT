/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-mee <rvan-mee@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 14:40:15 by rvan-mee      #+#    #+#                 */
/*   Updated: 2022/10/26 21:46:31 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <minirt.h>

typedef void	(*t_job)(t_minirt *, void *);

// add_job_node.c
bool	add_new_job_node(t_minirt *data, t_job job, void *job_param);

//	create_render_lst.c
bool	create_render_queue(t_minirt *data);

//	create_rays.c
bool	create_rays(t_minirt *data, t_render *block);

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
