/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fast_dda.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/21 20:25:45 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 14:42:11 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

/*
** See A Fast Voxel Traversal Algorithm For Ray Tracing
** By john Amanatides & Andrew Woo
** I just add the side variable for texture and distance
**/

/*
** I was eating crackers, crumbs were falling on my keyboard, when I thought : 
** I certainly have a crust issue...
** ...
** Ah. Ah.
*/

/*
** I'll try to add more jokes to my codes (it's funnier than working)
*/

t_vector2	get_tmax_n_side(t_vector2 *delta, t_vector2 *dir, t_vector2 *pos, int *side)
{
	t_vector2 tmax;

	if (dir->x > 0)
		tmax.x = (ceil(pos->x) - pos->x) * delta->x;
	else
		tmax.x = (pos->x - floor(pos->x)) * delta->x;
	if (dir->y > 0)
		tmax.y = (ceil(pos->y) - pos->y) * delta->y;
	else
		tmax.y = (pos->y - floor(pos->y)) * delta->y;
	if (tmax.x != tmax.x)
		tmax.x = HUGE_VAL;
	if (tmax.y != tmax.y)
		tmax.y = HUGE_VAL;
	*side = 1;
	return (tmax);
}

int		is_in_map(t_point pos, t_point size)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y)
		return (0);
	return (1);
}

t_intersection	get_inter(t_point pos, int side, t_map *map, t_vector2 tmax)
{
	t_intersection inter;

	inter.hit = pos;
	inter.side = side;
	inter.exact_hit = tmax; // in fact t_max + pos (but don't have the real pos here)
	inter.dist = 0; //later, we need to project it on the dir of cam
	if (is_in_map(pos, map->map_size))
		inter.block = map->map[pos.y][pos.x].type;
	else
		inter.block = 0;
	return (inter);
}

t_intersection	fast_dda(t_vector2 dir, t_vector2 pos, t_map *map)
{
	t_vector2	delta;
	t_vector2	tmax;
	t_point		step;
	t_point		ipos;
	int			side;

	ipos = init_point(floor(pos.x), floor(pos.y));
	step = init_point((int)copysign(1, dir.x), (int)copysign(1, dir.y));
	delta =init_vector2(fabs(1 / dir.x), fabs(1 / dir.y));
	tmax = get_tmax_n_side(&delta, &dir, &pos, &side);
	while (is_in_map(ipos, map->map_size) && map->map[ipos.y][ipos.x].type == 0)
	{
		if (tmax.x < tmax.y && !(side = 0))
		{
			tmax.x += delta.x;
			ipos.x += step.x;
		}
		else
		{
			side = 1;
			tmax.y += delta.y;
			ipos.y += step.y;
		}
	}
	return (get_inter(ipos, side, map, tmax));
}
