/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   point.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/20 21:22:20 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/20 21:23:29 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

t_point	init_point(int x, int y)
{
	t_point ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}