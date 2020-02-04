/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 21:51:04 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 21:31:38 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

double		vector2_norm(t_vector2 u)
{
	return (sqrt(u.x * u.x + u.y * u.y));
}

void		vector2_normalize(t_vector2 *u)
{
	double tmp;

	tmp = 1. / sqrt(u->x * u->x + u->y * u->y);
	u->x *= tmp;
	u->y *= tmp;
}

t_vector2	vector2_ortho_cw(t_vector2 u)
{
	t_vector2 ret;

	ret.x = u.y;
	ret.y = -u.x;
	return (ret);
}

t_vector2	vector2_ortho_ccw(t_vector2 u)
{
	t_vector2 ret;

	ret.x = -u.y;
	ret.y = u.x;
	return (ret);
}
