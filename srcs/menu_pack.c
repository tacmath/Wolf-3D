/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   menu_pack.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 16:07:12 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 16:07:27 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void print_pack_return(t_wolf *wolf)
{
    t_point start;
    int x;
    int y;
    
    start.x = SCREEN_X / 2 - wolf->menu.button_size.w / 2;
    start.y = SCREEN_Y - ((SCREEN_Y / 2 - SELECT_ZONE_H / 2) / 2 + wolf->menu.button_size.h / 2);
    if (wolf->mouse_pos.x >= start.x && wolf->mouse_pos.x < start.x + wolf->menu.button_size.w
        && wolf->mouse_pos.y >= start.y && wolf->mouse_pos.y < start.y + wolf->menu.button_size.h)
    {
        y = -1;
        while (++y < wolf->menu.button_size.h)
        {
            x = -1;
            while (++x < wolf->menu.button_size.w)
                wolf->ml->img_data[x + start.x + (y + start.y) * SCREEN_X] =  wolf->menu.button[3][1][wolf->menu.button_size.w * y + x];
        }
    }
    else
    {
        y = -1;
        while (++y < wolf->menu.button_size.h)
        {
            x = -1;
            while (++x < wolf->menu.button_size.w)
                wolf->ml->img_data[x + start.x + (y + start.y) * SCREEN_X] =  wolf->menu.button[3][0][wolf->menu.button_size.w * y + x];
        }
    }
    mlx_put_image_to_window(wolf->ml->mlx_ptr, wolf->ml->win_ptr, wolf->ml->img, 0, 0);
}

void print_pack_button(t_wolf *wolf)
{
    int n;
    int x;
    int y;
    
    n = -1;
    while (++n < wolf->menu.pack.nb_max)
    {
        y = -1;
        while (++y < wolf->menu.pack.name_size.h)
        {
            x = -1;
            while (++x < wolf->menu.pack.name_size.w)
            {
                wolf->ml->img_data[x + SCREEN_X / 2 - wolf->menu.pack.name_size.w / 2
                                   + (y + wolf->menu.pack.start + wolf->menu.pack.delta * n) * SCREEN_X] =
                wolf->menu.pack.name[n + wolf->menu.pack.nb_start][y * wolf->menu.pack.name_size.w + x];
            }
        }
    }
    print_pack_return(wolf);
}

void print_pack(t_wolf *wolf)
{
    int x;
    int y;
    int n;
    
    fill_menu_background(wolf, 1);
    y = -1;
    while (++y < SELECT_ZONE_H)
    {
        x = -1;
        while (++x < SELECT_ZONE_W)
        {
            n = (y + (SCREEN_Y - SELECT_ZONE_H) / 2) * SCREEN_X + x + (SCREEN_X - SELECT_ZONE_W) / 2;
            wolf->ml->img_data[n] = ((((wolf->ml->img_data[n] >> 16) & 0xFF) / 2) << 16)
            + ((((wolf->ml->img_data[n] >> 8) & 0xFF) / 2) << 8) + (wolf->ml->img_data[n] & 0xFF) / 2;
            
        }
    }
    print_pack_button(wolf);
}

void        check_pack_button(t_wolf *wolf, int x, int y)
{
    int n;
    t_point start;
    
    start.x = SCREEN_X / 2 - wolf->menu.button_size.w / 2;
    start.y = SCREEN_Y - ((SCREEN_Y / 2 - SELECT_ZONE_H / 2) / 2 + wolf->menu.button_size.h / 2);
    if (wolf->mouse_pos.x >= start.x && wolf->mouse_pos.x < start.x + wolf->menu.button_size.w
        && wolf->mouse_pos.y >= start.y && wolf->mouse_pos.y < start.y + wolf->menu.button_size.h)
    {
        wolf->mode = MENU;
        print_menu(wolf);
        return ;
    }
    n = -1;
    while (++n < wolf->menu.pack.nb_max)
        if (x >= (SCREEN_X - wolf->menu.pack.name_size.w) / 2 && x <= (SCREEN_X + wolf->menu.pack.name_size.w) / 2 &&
            y >= wolf->menu.pack.start + wolf->menu.pack.delta * n && y <= wolf->menu.pack.start
            + wolf->menu.pack.delta * n + wolf->menu.pack.name_size.h)
        {
            free_data(wolf);
            load_pack(wolf, wolf->packs[n + wolf->menu.pack.nb_start]);
            print_pack(wolf);
            return ;
        }
}
