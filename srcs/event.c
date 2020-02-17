/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:23:32 by lperron           #+#    #+#             */
/*   Updated: 2020/02/16 18:24:02 by lperron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <unistd.h>
#include <stdlib.h>

int		deal_motion(int x, int y, t_wolf *wolf)
{
	wolf->mouse_pos.x = x;
	wolf->mouse_pos.y = y;
	return (1);
}

int		ft_destroy(t_wolf *wolf)
{
	free_wolf(wolf);
	exit(1);
	return (1);
}
