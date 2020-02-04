/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 16:15:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 15:49:54 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void    free_wolf(t_wolf *wolf)
{
    int n;
    
    if (wolf->map->map)
    {
        n = -1;
        while (++n < wolf->map->map_size.y)
            free(wolf->map->map[n]);
        free(wolf->map->map);
    }
    mlx_destroy_image(wolf->ml->mlx_ptr, wolf->ml->img);
    mlx_destroy_window(wolf->ml->mlx_ptr, wolf->ml->win_ptr);
    free(wolf->ml->mlx_ptr);
}

static void    free_textures(t_wolf *wolf)
{
    int n;
    int m;
    
    n = -1;
    while (++n < wolf->nb_textures)
    {
        if (wolf->textures[n][0])
        {
            m = -1;
            while (++m < wolf->texture_size.w)
                free(wolf->textures[n][0][m]);
            free(wolf->textures[n][0]);
        }
        if (wolf->textures[n][1])
        {
            m = -1;
            while (++m < wolf->texture_size.w)
                free(wolf->textures[n][1][m]);
            free(wolf->textures[n][1]);
        }
        free(wolf->textures[n]);
    }
    free(wolf->textures);
}

static void    free_sprites(t_wolf *wolf)
{
    int n;
    int m;
    
    n = -1;
    while (++n < wolf->nb_sprites)
    {
        if (wolf->sprites[n])
        {
            m = -1;
            while (++m < wolf->sprites_size.w)
                free(wolf->sprites[n][m]);
			free(wolf->sprites[n]);
        }
    }
    free(wolf->sprites);
}

static void    free_menu(t_menu menu)
{
    int n;
    
    n = -1;
    while (++n < 4)
        free(menu.menu[n]);
    n = -1;
    while (++n < 5)
    {
        free(menu.button[n][0]);
        free(menu.button[n][1]);
    }
    free(menu.background);
}

void    free_data(t_wolf *wolf)
{
    free_menu(wolf->menu);
    free_textures(wolf);
	free_sprites(wolf);
	free(wolf->skybox);
}
