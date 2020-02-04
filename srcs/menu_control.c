/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   menu_control.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 16:03:58 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 16:04:23 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void print_controls(t_wolf *wolf, t_button button, int color)
{
    int x;
    int y;
    
    y = -1;
    while (++y < button.h)
    {
        x = -1;
        while (++x < button.w)
            wolf->ml->img_data[(y + button.y) * SCREEN_X + button.x + x] = color;
    }
}

void print_control_button(t_wolf *wolf)
{
    int n;
    static int image[BUTTON_CONTROLS] = {-1, -1, -1, -1, -1, 3};
    
    n = -1;
    while (++n < BUTTON_CONTROLS)
        if (wolf->mouse_pos.x >= wolf->button.controls[n].x && wolf->mouse_pos.y >= wolf->button.controls[n].y
            && wolf->mouse_pos.x <= wolf->button.controls[n].x + wolf->button.controls[n].w
            && wolf->mouse_pos.y <= wolf->button.controls[n].y + wolf->button.controls[n].h)
        {
            if (image[n] == -1)
                print_controls(wolf, wolf->button.controls[n], 0x777777);
            else
                print_button(wolf, wolf->button.controls[n], wolf->menu.button[image[n]][1]);
        }
        else
        {
            if (image[n] == -1)
                print_controls(wolf, wolf->button.controls[n], 0xDDDDDD);
            else
                print_button(wolf, wolf->button.controls[n], wolf->menu.button[image[n]][0]);
        }
    mlx_put_image_to_window(wolf->ml->mlx_ptr, wolf->ml->win_ptr, wolf->ml->img, 0, 0);
}

void print_control(t_wolf *wolf)
{
    fill_menu_background(wolf, 3);
    print_control_button(wolf);
}
