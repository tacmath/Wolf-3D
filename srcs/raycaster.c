/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:12:40 by lperron           #+#    #+#             */
/*   Updated: 2020/02/16 17:03:01 by lperron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

void	get_dist_projected(t_intersection *inter, t_vector2 dir, t_vector2 pos)
{
	if (inter->side)
	{
		if (dir.y > 0)
			inter->dist = (inter->hit.y - pos.y) / dir.y;
		else
			inter->dist = (inter->hit.y + 1 - pos.y) / dir.y;
	}
	else
	{
		if (dir.x > 0)
			inter->dist = (inter->hit.x - pos.x) / dir.x;
		else
			inter->dist = (inter->hit.x + 1 - pos.x) / dir.x;
	}
}

void	get_text_col(t_intersection *inter, t_vector2 dir,
		t_vector2 pos, int texture_size)
{
	double	deci_hit;
	int		text_col;

	if (inter->side)
		deci_hit = (pos.x + inter->dist * dir.x);
	else
		deci_hit = (pos.y + inter->dist * dir.y);
	text_col = (deci_hit - floor(deci_hit)) * (texture_size - 1);
	inter->text_col = (text_col);
}

void	draw_col(t_wolf *wolf, int x, t_intersection inter, double angle)
{
	unsigned int	*text_c;
	int				height;
	int				offset;
	double			delta;
	t_point			i;

	inter.dist *= cos((angle) * 0.01745329251);
	inter.dist *= 0.5;
	height = SCREEN_Y / inter.dist;
	text_c = wolf->textures[(int)inter.block][(int)inter.side][inter.text_col];
	offset = (SCREEN_Y - height) / 2 + wolf->offset;
	delta = wolf->texture_size.h / (double)height;
	i = init_point(0, 0);
	if (offset < 0)
	{
		i.y = -offset;
		offset = 0;
	}
	if (offset + height > SCREEN_Y)
		height = SCREEN_Y - offset;
	while (i.x < height)
		wolf->ml->img_data[SCREEN_X * (offset + i.x++) + x] =
			text_c[(int)(i.y++ * delta)];
}

void	fill_col_info(t_wolf *wolf, int x, t_intersection inter, double angle)
{
	t_test		test;

	inter.dist *= cos((angle) * 0.01745329251);
	inter.dist *= 0.5;
	test.height = SCREEN_Y / inter.dist;
	if (inter.block >= wolf->nb_textures)
	{
		inter.block = inter.block % wolf->nb_textures;
		if (!inter.block)
			inter.block = 1;
	}
	if (inter.block == 0)
		test.height = 0;
	test.text_c =
	(int *)wolf->textures[(int)inter.block][(int)inter.side][inter.text_col];
	test.offset = (SCREEN_Y - test.height) / 2 + wolf->offset;
	test.delta = wolf->texture_size.h / (double)(test.height);
	wolf->test[x] = test;
}

void	raycaster_col(t_wolf *wolf, int x, double angle, t_vector2 dir_ray)
{
	t_intersection	inter;

	vector2_rotate(&dir_ray, angle);
	inter = fast_dda(dir_ray, wolf->pos, wolf->map);
	get_dist_projected(&inter, dir_ray, wolf->pos);
	get_text_col(&inter, dir_ray, wolf->pos, wolf->texture_size.w);
	fill_col_info(wolf, x, inter, angle);
}

double	mod(double x)
{
	while (x < 0)
		x += 360;
	while (x > 360)
		x -= 360;
	return (x);
}

void	draw_all(t_wolf *wolf)
{
	int		startx;
	int		x;
	int		y;
	int		*screen;
	t_test	*test;

	wolf->offset += SCREEN_Y / 2;
	if (wolf->skybox) // wow, uncomment this line and put startx @ 0 then 9999999999
		startx = mod(wolf->dir_angle - wolf->fov / 2.) / 360. * wolf->skybox_size.w; //why this line cost 50FPS?
	y = -1;
	screen = (int*)wolf->ml->img_data;
	while (++y < SCREEN_Y && (x = -1))
	{
		test = wolf->test;
		while (++x < SCREEN_X)
		{
			if (y > test->offset && y < test->offset + test->height)
			{
				*screen = test->text_c[(int)((y - test->offset) * test->delta)];
			}
			else if (y < wolf->offset)
			{
				if (wolf->skybox == 0)
					*screen = wolf->roof;
				else
					*screen = wolf->skybox[wolf->skybox_size.w * y + x + startx];
			}
			else
				*screen = wolf->floor;
			screen++;
			test++;
		}
	}
}

void	test_draw_no_par(t_wolf *wolf)
{
	int		i;
	double	delta_deg;
	double	angle;

	delta_deg = wolf->fov / (double)SCREEN_X;
	angle = -wolf->fov / 2.;
	i = -1;
	bzero_vis(wolf);
	while (++i < SCREEN_X)
	{
		raycaster_col(wolf, i, angle, wolf->dir);
		angle += delta_deg;
	}
	draw_all(wolf);
	more_viz_pleaz(wolf);
	compute_obj_dist(wolf);
	draw_all_obj(wolf);
}
