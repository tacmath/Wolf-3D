/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rotate.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 22:10:15 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 15:09:09 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void		vector2_rotate(t_vector2 *u, double th)
{
	double	si;
	double	co;
	double	angle;
	double tmpx;

	angle = th / 57.2957795131;
	si = sin(angle);
	co = cos(angle);
	tmpx = u->x;
	u->x = u->x * co - u->y * si;
	u->y = tmpx * si + u->y * co;
}
