/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperron <lperron@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:14:11 by lperron           #+#    #+#             */
/*   Updated: 2020/02/16 18:22:44 by lperron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static char		check_button(t_wolf *wolf, t_button *buttons, int nb_buttons,
		t_point coord)
{
	int n;

	n = -1;
	while (++n < nb_buttons)
		if (coord.x >= buttons[n].x && coord.y >= buttons[n].y
				&& coord.x <= buttons[n].x + buttons[n].w
				&& coord.y <= buttons[n].y + buttons[n].h)
		{
			buttons[n].function(wolf);
			return (n);
		}
	return (-1);
}

int				deal_button_release(int button, int x, int y, t_wolf *wolf)
{
	int n;

	(void)x;
	(void)y;
	n = -1;
	while (++n < 7)
		if (wolf->key_used[n] == button + 1000)
		{
			wolf->key[n] = 0;
			break ;
		}
	return (1);
}

static int		deal_button2(int button, int x, int y, t_wolf *wolf)
{
	int		n;
	t_point	coord;

	if (button == RIGHT_CLICK)
	{
		coord.x = x;
		coord.y = y;
		if (wolf->mode == MENU)
			check_button(wolf, wolf->button.menu, BUTTON_MENU, coord);
		else if (wolf->mode == CONTROLS)
			wolf->button.button_pressed = check_button(wolf,
					wolf->button.controls, BUTTON_CONTROLS, coord);
		else if (wolf->mode == PACK)
			check_pack_button(wolf, x, y);
	}
	n = -1;
	while (++n < 7)
		if (wolf->key_used[n] == button + 1000)
		{
			wolf->key[n] = 1;
			break ;
		}
	return (1);
}

int				deal_button(int button, int x, int y, t_wolf *wolf)
{
	if (wolf->get_key && button < 4)
	{
		wolf->key[(int)wolf->button.button_pressed] = 0;
		wolf->key_used[(int)wolf->button.button_pressed] = button + 1000;
		wolf->get_key = FALSE;
		return (1);
	}
	if (wolf->mode == PACK)
	{
		if (button == 4 && wolf->menu.pack.nb_start > 0)
		{
			wolf->menu.pack.nb_start--;
			print_pack_button(wolf);
		}
		else if (button == 5 && wolf->menu.pack.nb_start +
				wolf->menu.pack.nb_max < wolf->menu.pack.nb)
		{
			wolf->menu.pack.nb_start++;
			print_pack_button(wolf);
		}
	}
	return (deal_button2(button, x, y, wolf));
}
