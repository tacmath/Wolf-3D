/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:10:22 by lperron           #+#    #+#             */
/*   Updated: 2020/02/16 16:10:25 by lperron          ###   ########lyon.fr   */
/*                                                                            */
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
