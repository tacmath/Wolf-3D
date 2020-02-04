/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycaster.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 01:35:42 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 17:31:54 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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

void	get_text_col(t_intersection *inter, t_vector2 dir, t_vector2 pos, int texture_size)
{
	double	deci_hit;
	int	text_col;

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
	int		height;
	int		offset;
	double		delta;
	t_point		i;

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
		wolf->ml->img_data[SCREEN_X * (offset + i.x++) + x] = text_c[(int)(i.y++ * delta)];
}

void    fill_col_info(t_wolf *wolf, int x, t_intersection inter, double angle)
{
	t_test		test;

        inter.dist *= cos((angle) * 0.01745329251);
        inter.dist *= 0.5;
        test.height = SCREEN_Y / inter.dist;
		if (inter.block >= wolf->nb_textures)
			inter.block = inter.block % wolf->nb_textures;
        test.text_c = wolf->textures[(int)inter.block][(int)inter.side][inter.text_col];
        test.offset = (SCREEN_Y - test.height) / 2 + wolf->offset;
        test.delta = wolf->texture_size.h / (double)(test.height);
	wolf->test[x] = test;
     /*   if (test.offset < 0)
        { 
                i.y = -offset;
                offset = 0;
        }
        if (offset + height > SCREEN_Y)
                height = SCREEN_Y - offset;*/
}    

void	raycaster_col(t_wolf *wolf, int x, double angle, t_vector2 dir_ray)
{
	t_intersection	inter;

	vector2_rotate(&dir_ray, angle);
	inter = fast_dda(dir_ray, wolf->pos, wolf->map);
	get_dist_projected(&inter, dir_ray, wolf->pos);
	get_text_col(&inter, dir_ray, wolf->pos, wolf->texture_size.w);
	fill_col_info(wolf, x, inter,angle);
//	draw_col(wolf, x, inter, angle);
}

void	draw_all(t_wolf *wolf)
{
	int x;
	int y;

	wolf->offset += SCREEN_Y / 2;
	y = -1;
	while (++y < SCREEN_Y)
	{
		x = -1;
		while (++x < SCREEN_X)
		{
			if (y > wolf->test[x].offset && y < wolf->test[x].offset+ wolf->test[x].height)
			{
				wolf->ml->img_data[SCREEN_X * y + x] = wolf->test[x].text_c[(int)((y - wolf->test[x].offset) * wolf->test[x].delta)];
			}
			else if (y < wolf->offset)
			{
				wolf->ml->img_data[SCREEN_X * y + x] = wolf->roof;
			}
			else
				wolf->ml->img_data[SCREEN_X * y + x] = wolf->floor;
		}
	}
}

void	test_draw_no_par(t_wolf *wolf)
{
	int	i;
	double	delta_deg;
	double	angle;

	delta_deg = wolf->fov / (double)SCREEN_X;
	angle = -wolf->fov / 2.;
	i = -1;
	while (++i < SCREEN_X)
	{
		raycaster_col(wolf, i, angle, wolf->dir);
		angle += delta_deg;
	}
	draw_all(wolf);
}
