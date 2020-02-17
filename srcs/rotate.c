/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:11:27 by lperron           #+#    #+#             */
/*   Updated: 2020/02/16 16:11:36 by lperron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		vector2_rotate(t_vector2 *u, double th)
{
	double	si;
	double	co;
	double	angle;
	double	tmpx;

	angle = th / 57.2957795131;
	si = sin(angle);
	co = cos(angle);
	tmpx = u->x;
	u->x = u->x * co - u->y * si;
	u->y = tmpx * si + u->y * co;
}
