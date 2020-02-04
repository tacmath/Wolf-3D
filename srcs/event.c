/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 14:05:43 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 17:57:39 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
