/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:09:43 by lperron           #+#    #+#             */
/*   Updated: 2020/02/16 16:10:14 by lperron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_vector2	init_vector2(double x, double y)
{
	t_vector2	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

double		vector2_scalar(t_vector2 u, t_vector2 v)
{
	return (u.x * v.x + u.y * v.y);
}

t_vector2	vector2_sub(t_vector2 u, t_vector2 v)
{
	t_vector2 ret;

	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	return (ret);
}

t_vector2	vector2_add(t_vector2 u, t_vector2 v)
{
	t_vector2 ret;

	ret.x = u.x + v.x;
	ret.y = u.y + v.y;
	return (ret);
}

t_vector2	vector2_lambda_mult(double lambda, t_vector2 u)
{
	t_vector2 ret;

	ret.x = lambda * u.x;
	ret.y = lambda * u.y;
	return (ret);
}
