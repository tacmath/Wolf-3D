/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_event.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 16:12:44 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:15:40 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

int        deal_key_up(int key, t_wolf *wolf)
{
    int n;
    
    if (key == ESCAPE_KEY)
    {
        if (wolf->mode != RUNING)
        {
            if (wolf->mode == PACK || wolf->mode == CONTROLS)
            {
                wolf->mode = MENU;
                print_menu(wolf);
            }
            else
			{
                wolf->mode = RUNING;
				mlx_mouse_hide(wolf->ml->mlx_ptr, wolf->ml->win_ptr);
				mlx_mouse_move(wolf->ml->mlx_ptr, wolf->ml->win_ptr, SCREEN_X / 2, SCREEN_Y / 2);
				wolf->mouse_pos.x = SCREEN_X / 2;
				wolf->mouse_pos.y = SCREEN_Y / 2;
			}
        }
        else
        {
			mlx_mouse_show(wolf->ml->mlx_ptr, wolf->ml->win_ptr);
            print_menu(wolf);
            wolf->mode = MENU;
        }
    }
    else
    {
        if (wolf->get_key)
        {
            wolf->key[(int)wolf->button.button_pressed] = 0;
            wolf->key_used[(int)wolf->button.button_pressed] = key;
            wolf->get_key = FALSE;
            return (1);
        }
        n = -1;
        while (++n < 7)
            if (wolf->key_used[n] == key)
            {
                wolf->key[n] = 0;
                break ;
            }
    }
    return (1);
}

int        deal_key_down(int key, t_wolf *wolf)
{
    int n;
    
    n = -1;
    while (++n < 7)
        if (wolf->key_used[n] == key)
        {
            wolf->key[n] = 1;
            break ;
        }
    return (1);
}
