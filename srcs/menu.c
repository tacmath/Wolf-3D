/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   menu.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 16:00:43 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 16:00:45 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void fill_menu_background(t_wolf *wolf, int menu)
{
    int n;
    int x;
    int y;
    
    if (wolf->menu.background)
    {
        n = -1;
        while (++n < SCREEN_X * SCREEN_Y)
            wolf->ml->img_data[n] = wolf->menu.background[n];
    }
    else
    {
        n = -1;
        while (++n < SCREEN_X * SCREEN_Y)
            wolf->ml->img_data[n] = wolf->menu.background_color;
    }
    y = -1;
    while (++y < wolf->menu.menu_size.h)
    {
        x = -1;
        while (++x < wolf->menu.menu_size.w)
            wolf->ml->img_data[y * SCREEN_X + (SCREEN_X - wolf->menu.menu_size.w) / 2 + x] = wolf->menu.menu[menu][y * wolf->menu.menu_size.w + x];
    }
}

void print_button(t_wolf *wolf, t_button button, unsigned int *image)
{
    int x;
    int y;
    
    y = -1;
    while (++y < button.h)
    {
        x = -1;
        while (++x < button.w)
        {
            wolf->ml->img_data[(y + button.y) * SCREEN_X + button.x + x] = image[y * button.w + x];
        }
    }
}

void print_menu_button(t_wolf *wolf)
{
    int n;
    static int image[BUTTON_MENU] = {0, 2, 3, 4};
    
    n = -1;
    while (++n < BUTTON_MENU)
        if (wolf->mouse_pos.x >= wolf->button.menu[n].x && wolf->mouse_pos.y >= wolf->button.menu[n].y
            && wolf->mouse_pos.x <= wolf->button.menu[n].x + wolf->button.menu[n].w
            && wolf->mouse_pos.y <= wolf->button.menu[n].y + wolf->button.menu[n].h)
        {
            print_button(wolf, wolf->button.menu[n], wolf->menu.button[image[n]][1]);
        }
        else
            print_button(wolf, wolf->button.menu[n], wolf->menu.button[image[n]][0]);
    mlx_put_image_to_window(wolf->ml->mlx_ptr, wolf->ml->win_ptr, wolf->ml->img, 0, 0);
}

void print_menu(t_wolf *wolf)
{
    fill_menu_background(wolf, 0);
    print_menu_button(wolf);
}
