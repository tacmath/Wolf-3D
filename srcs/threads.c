/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   threads.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/13 14:56:49 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 21:08:21 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

int	col_thread(void *dt)
{
	t_thread_data	*data;

	data = (t_thread_data *)dt;
	while (data->strt < SCREEN_X)
	{
		raycaster_col((data->wolf), data->strt, data->angle, data->dir);
		data->strt += NB_THREAD;
		data->angle += data->delta_angle;
	}
	return (0);
}

t_thread_data	init_thread_data(int i, t_wolf *wolf, double angle, double delta_deg)
{
	t_thread_data thr_data;

	thr_data.strt = i;
	thr_data.wolf = wolf;
	thr_data.angle = angle;
	thr_data.dir = wolf->dir;
	thr_data.delta_angle = delta_deg;
	return (thr_data);
}

void	draw_all_screen(t_wolf *wolf)
{
	int		i;
	double		delta_deg;
	double		delta_deg_mult;
	double		angle;
	t_thread_data	thr_data[NB_THREAD];

	i = 0;
	delta_deg = wolf->fov / (double)SCREEN_X;
	delta_deg_mult = NB_THREAD * delta_deg;
	angle = -wolf->fov / 2.;
	//vector2_normalize(&wolf->dir);
	while (i < NB_THREAD)
	{
		thr_data[i] = init_thread_data(i, wolf, angle, delta_deg_mult);
		pthread_create(&(wolf->thr[i]), NULL, (void*)col_thread, &(thr_data[i]));
		angle += delta_deg;
		i++;
	}
	i = -1;
	while (++i < NB_THREAD)
		pthread_join(wolf->thr[i], NULL);
}
