/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:05:06 by lperron           #+#    #+#             */
/*   Updated: 2020/02/16 16:07:34 by lperron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		bzero_vis(t_wolf *wolf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < wolf->map->map_size.y)
	{
		x = -1;
		while (++x < wolf->map->map_size.x)
			wolf->map->map[y][x].vis = 0;
	}
}

/*
** here we just put a 2 in each 0 cell touching a 1 cell
** (sides n edges can touch)
** ('cause object can be on two cells at the same time :'(  )
**
** 0 1 1 1 1 0         2 1 1 1 1 2
** 0 0 1 1 1 0   __    2 2 1 1 1 2
** 0 0 1 1 0 0      \  0 2 1 1 2 2
** 0 0 0 1 0 0   __ /  0 2 2 1 2 0
** 0 0 0 1 0 0         0 0 2 1 2 0
** 0 0 0 0 0 0         0 0 2 2 2 0
*/

static int	check_near_cells(t_map *m, int x, int y)
{
	if (x > 0)
	{
		if (m->map[y][x - 1].vis == 1)
			return (1);
		if (y > 0 && m->map[y - 1][x - 1].vis == 1)
			return (1);
		if (y < m->map_size.y - 1 && m->map[y + 1][x - 1].vis == 1)
			return (1);
	}
	if (x < m->map_size.x - 1)
	{
		if (m->map[y][x + 1].vis == 1)
			return (1);
		if (y > 0 && m->map[y - 1][x + 1].vis == 1)
			return (1);
		if (y < m->map_size.y - 1 && m->map[y + 1][x + 1].vis == 1)
			return (1);
	}
	if (y > 0 && m->map[y - 1][x].vis == 1)
		return (1);
	if (y < m->map_size.y - 1 && m->map[y + 1][x].vis == 1)
		return (1);
	return (0);
}

void		print_viz(t_wolf *wolf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < wolf->map->map_size.y)
	{
		x = -1;
		while (++x < wolf->map->map_size.x)
		{
			ft_printf("%d ", wolf->map->map[y][x].vis);
		}
		ft_printf("\n");
	}
	ft_printf("\n\n\n");
}

void		more_viz_pleaz(t_wolf *wolf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < wolf->map->map_size.y)
	{
		x = -1;
		while (++x < wolf->map->map_size.x)
		{
			if (wolf->map->map[y][x].vis == 0 &&
				check_near_cells(wolf->map, x, y))
			{
				wolf->map->map[y][x].vis = 2;
			}
		}
	}
}
