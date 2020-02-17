/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:42:39 by lperron           #+#    #+#             */
/*   Updated: 2020/02/17 16:05:16 by lperron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		cmp_dist(void *obj1, void *obj2)
{
	t_object	*tmp1;
	t_object	*tmp2;
	double		dist1;
	double		dist2;

	tmp1 = (t_object *)obj1;
	tmp2 = (t_object *)obj2;
	dist1 = tmp1->dist;
	dist2 = tmp2->dist;
	if (dist1 == -1)
		return (0);
	if (dist2 == -1)
		return (1);
	return (dist2 - dist1);
}

void	compute_obj_dist(t_wolf *wo)
{
	t_vector2	rel;
	int			i;

	i = -1;
	while (++i < wo->nb_obj)
	{
		if (wo->map->map[(int)wo->obj[i].pos.y][(int)wo->obj[i].pos.x].vis == 0)
		{
			wo->obj[i].dist = -1;
		}
		else
		{
			rel.x = wo->obj[i].pos.x - wo->pos.x;
			rel.y = wo->obj[i].pos.y - wo->pos.y;
			wo->obj[i].dist = sqrt(rel.x * rel.x + rel.y * rel.y);
			wo->obj[i].rel = rel;
		}
	}
	ft_quicksort((void*)wo->obj, i, sizeof(t_object), cmp_dist);
}

t_point	get_start(t_wolf *wolf, t_object *obj)
{
	double	angle;
	t_point	start;
	int		height;
	double	delta_pix;

	delta_pix = SCREEN_X / (double)wolf->fov;
	angle = vector2_scalar(wolf->dir, obj->rel) / obj->dist;
	obj->dist *= 0.5;
	angle = (acos(angle)) * 57.295779513;
	if (vector2_scalar(obj->rel, vector2_ortho_ccw(wolf->dir)) < 0)
		angle *= -1;
	height = (SCREEN_Y / obj->dist);
	start.x = (angle + wolf->fov / 2.) * delta_pix - height / 2.;
	start.y = -height / 2. + wolf->offset;
	return (start);
}

void	draw_obj(t_wolf *wolf, t_object *obj)
{
	int		h;
	t_point	i;
	double	delta;
	t_point	start;
	int		pix;

	start = get_start(wolf, obj);
	h = (SCREEN_Y / obj->dist);
	delta = wolf->sprites_size.h / (double)h;
	i.y = start.y < 0 ? -start.y : 0;
	while (i.y < h && i.y + start.y < SCREEN_Y)
	{
		i.x = start.x < 0 ? -start.x : 0;
		while (i.x < h && i.x + start.x < SCREEN_X)
		{
			pix = wolf->sprites[obj->sprites[0] %
				wolf->nb_sprites][(int)(i.x * delta)][(int)(i.y * delta)];
			if (pix != NOCOLOR && h >= wolf->test[ i.x + start.x].height)
				wolf->ml->img_data[(start.y + i.y)
					* SCREEN_X + i.x + start.x] = pix;
			i.x++;
		}
		i.y++;
	}
}

void	draw_all_obj(t_wolf *wolf)
{
	int	i;

	i = -1;
	while (++i < wolf->nb_obj)
	{
		if (wolf->obj[i].dist != -1)
			draw_obj(wolf, &wolf->obj[i]);
	}
}
