/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   controls.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 19:09:13 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 16:22:20 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void build_a_wall(t_wolf *wolf, t_vector2 new_pos)
{
	if (wolf->map->map[(int)(new_pos.y - 0.2)][(int)wolf->pos.x].type)
			wolf->pos.y = (int)wolf->pos.y + 0.2;
	else if (wolf->map->map[(int)(new_pos.y + 0.2)][(int)wolf->pos.x].type)
		wolf->pos.y = (int)wolf->pos.y + 1 - 0.2;
	else
		wolf->pos.y = new_pos.y;
	if (wolf->map->map[(int)wolf->pos.y][(int)(new_pos.x - 0.2)].type)
			wolf->pos.x = (int)wolf->pos.x + 0.2;
	else if (wolf->map->map[(int)wolf->pos.y][(int)(new_pos.x + 0.2)].type)
			wolf->pos.x = (int)wolf->pos.x + 1 - 0.2;
	else
		wolf->pos.x = new_pos.x;
}
/*
void	handle_mouse(t_wolf *wolf)
{
	double	center;
	double	middle;
	double	delta;

	middle = SCREEN_X / 2.;
	center = SCREEN_X * 0.1;
	delta = wolf->mouse_pos.x - middle;
	if (fabs(delta) > center)
	{
		delta += delta < center ? center : -center;
		delta *= fabs(delta / 2.);
		wolf->dir_angle += delta * 0.00001;
		vector2_rotate(&wolf->dir, delta * 0.00001);
	}
}*/

void	handle_mouse(t_wolf *wolf)
{
	vector2_rotate(&wolf->dir, (wolf->mouse_pos.x - (SCREEN_X / 2)) * 0.2);
	mlx_mouse_move(wolf->ml->win_ptr, SCREEN_X / 2, SCREEN_Y / 2);
	wolf->mouse_pos.x = SCREEN_X / 2;
	wolf->mouse_pos.y = SCREEN_Y / 2;
}

double springt(t_wolf *wolf)
{
	double speed;

	speed = 0.1;
	if (wolf->springt && wolf->springt < 20)
		wolf->springt += 1;
	else
		wolf->springt = 0;
	if (wolf->key[SPRINGT] && wolf->key[FORWARD])
	{
		if (wolf->springt == 0 && wolf->stamina)
			wolf->springt = 1;
		if (wolf->stamina >= 1)
		{
			speed += wolf->key[SPRINGT] * 0.1;
			wolf->stamina -= 1;
		}
	}
	else if (wolf->stamina < 300)
			wolf->stamina += 1;
	if (wolf->springt <= 10)
		wolf->offset = wolf->springt;
	else
		wolf->offset = 20 - (wolf->springt - 20);
	return (speed);
}


void use_key(t_wolf *wolf)
{
	t_vector2	new_pos;
	t_vector2	perp;
	double		speed;

	speed = springt(wolf);;
	if (wolf->key[LOOK_L])
	{
		wolf->dir_angle -=2;
		vector2_rotate(&wolf->dir, -2);
	}
	if (wolf->key[LOOK_R])
	{
		wolf->dir_angle +=2;
		vector2_rotate(&wolf->dir, 2);
	}
	if (wolf->key[FORWARD])
	{
		new_pos.y = wolf->pos.y + speed * wolf->dir.y;
		new_pos.x = wolf->pos.x + speed * wolf->dir.x;
		build_a_wall(wolf, new_pos);
	}
	if (wolf->key[BACKWARD])
	{
		new_pos.y = wolf->pos.y - speed * wolf->dir.y;
		new_pos.x = wolf->pos.x - speed * wolf->dir.x;
		build_a_wall(wolf, new_pos);
	}
	if (wolf->key[MOVE_L])
	{
		perp = vector2_ortho_cw(wolf->dir);
		new_pos.y = wolf->pos.y + speed * perp.y;
		new_pos.x = wolf->pos.x + speed * perp.x;
		build_a_wall(wolf, new_pos);
	}
	if (wolf->key[MOVE_R])
	{
		perp = vector2_ortho_cw(wolf->dir);
		new_pos.y = wolf->pos.y - speed * perp.y;
		new_pos.x = wolf->pos.x - speed * perp.x;
		build_a_wall(wolf, new_pos);
	}
	handle_mouse(wolf);
}
