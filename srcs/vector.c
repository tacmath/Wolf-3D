/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vector.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 21:24:57 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/20 21:48:41 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

t_vector2	init_vector2(double x, double y)
{
	t_vector2	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_vector2	vector2_scalar(t_vector2 u, t_vector2 v)
{
	t_vector2 ret;

	ret.x = u.x * v.x;
	ret.y = u.y * v.y;
	return (ret);
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
