/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_button.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/13 15:46:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:16:06 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void	control_button(t_wolf *wolf)
{
	wolf->get_key = TRUE;
}

void	exit_wolf(t_wolf *wolf)
{
	free_wolf(wolf);
	exit(1);
}

void	ft_return(t_wolf *wolf)
{
	wolf->mode--;
	if (wolf->mode == MENU)
		print_menu(wolf);
	if (wolf->mode == RUNING)
	{
		mlx_mouse_hide(wolf->ml->mlx_ptr, wolf->ml->win_ptr);
		mlx_mouse_move(wolf->ml->mlx_ptr, wolf->ml->win_ptr, SCREEN_X / 2, SCREEN_Y / 2);
		wolf->mouse_pos.x = SCREEN_X / 2;
		wolf->mouse_pos.y = SCREEN_Y / 2;
	}
}

void	controls_menu(t_wolf *wolf)
{
	wolf->mode = CONTROLS;
	print_control(wolf);
}

void    pack_menu(t_wolf *wolf)
{
        wolf->mode = PACK;
        print_pack(wolf);
}

static void init_button_menu(t_wolf *wolf)
{
	int delta;

	delta = (SCREEN_Y - (wolf->menu.menu_size.h + (SCREEN_Y - wolf->menu.menu_size.h) * 0.2)) / 4;
	wolf->button.menu[0].x = (SCREEN_X - wolf->menu.button_size.w) / 2;
	wolf->button.menu[0].y = wolf->menu.menu_size.h + (SCREEN_Y - wolf->menu.menu_size.h) * 0.1;
	wolf->button.menu[0].w = wolf->menu.button_size.w;
	wolf->button.menu[0].h = wolf->menu.button_size.h;
	wolf->button.menu[0].function = &controls_menu;
	ft_memcpy(&wolf->button.menu[1], &wolf->button.menu[0], sizeof(t_button));
	wolf->button.menu[1].function = &pack_menu;
	wolf->button.menu[1].y += delta;
	ft_memcpy(&wolf->button.menu[2], &wolf->button.menu[1], sizeof(t_button));
	wolf->button.menu[2].function = &ft_return;
	wolf->button.menu[2].y += delta;
	ft_memcpy(&wolf->button.menu[3], &wolf->button.menu[2], sizeof(t_button));
	wolf->button.menu[3].function = &exit_wolf;
	wolf->button.menu[3].y += delta;

}

static void init_button_controls(t_wolf *wolf)
{
	wolf->button.controls[0].x = SCREEN_X / 2 - 100;
	wolf->button.controls[0].y = wolf->menu.menu_size.h + SCREEN_Y * 0.1;
	wolf->button.controls[0].w = 200;
	wolf->button.controls[0].h = 70;
	wolf->button.controls[0].function = &control_button;
	ft_memcpy(&wolf->button.controls[1], &wolf->button.controls[0], sizeof(t_button));
	wolf->button.controls[1].y += SCREEN_Y / 10;
	ft_memcpy(&wolf->button.controls[2], &wolf->button.controls[1], sizeof(t_button));
	wolf->button.controls[2].y += SCREEN_Y / 10;
	ft_memcpy(&wolf->button.controls[3], &wolf->button.controls[2], sizeof(t_button));
	wolf->button.controls[3].y += SCREEN_Y / 10;
	ft_memcpy(&wolf->button.controls[4], &wolf->button.controls[3], sizeof(t_button));
	wolf->button.controls[4].y += SCREEN_Y / 10;
	ft_memcpy(&wolf->button.controls[5], &wolf->button.controls[4], sizeof(t_button));
	wolf->button.controls[5].y += SCREEN_Y / 10;
	wolf->button.controls[5].x = (SCREEN_X - wolf->menu.button_size.w) / 2;
	wolf->button.controls[5].w = wolf->menu.button_size.w;
	wolf->button.controls[5].h = wolf->menu.button_size.h;
	wolf->button.controls[5].function = &ft_return;
}

void init_button(t_wolf *wolf)
{
	init_button_menu(wolf);
	init_button_controls(wolf);
}
