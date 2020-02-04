/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_event.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 16:12:44 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 16:12:48 by mtaquet     ###    #+. /#+    ###.fr     */
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
                wolf->mode = RUNING;
        }
        else
        {
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
