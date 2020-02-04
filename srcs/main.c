/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 15:53:01 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 14:59:18 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"
#include <unistd.h>
#include <time.h>

void fill_background(t_wolf *wolf)
{
	int n;

	n = -1;
	while (++n < wolf->ml->nb_pxl / 2 + wolf->offset * SCREEN_X)
		wolf->ml->img_data[n] = wolf->roof;
	while (++n < wolf->ml->nb_pxl - wolf->offset * SCREEN_X)
		wolf->ml->img_data[n] = wolf->floor;
}

#include <stdio.h>

unsigned int	lempx_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	if ((r > 255) | (g > 255) | (b > 255))
		return (0);
	return ((r << 16) | (g << 8) | b);
}


void	show_fps(t_wolf *wolf, int fps)
{
	char	str[15];
	char	*sfps;

	ft_bzero(str, 15);
	ft_strcpy(str, "FPS : ");
	if (!(sfps = ft_itoa(fps)))
		return ;
	ft_strncat(str, sfps, 14 - 6);
	free(sfps);
	mlx_string_put(wolf->ml->mlx_ptr, wolf->ml->win_ptr,
			5, 15, lempx_rgb(255, 255, 255), str);

}

void	other_mode(t_wolf *wolf)
{
	static t_point old = {0, 0};

	if (old.x != wolf->mouse_pos.x && old.y != wolf->mouse_pos.y)
	{
		old = wolf->mouse_pos;
		if (wolf->mode == MENU)
			print_menu_button(wolf);
		else if (wolf->mode == CONTROLS)
			print_control_button(wolf);
		else if (wolf->mode == PACK)
			print_pack_return(wolf);
	}
}

void	print_stamina(t_wolf *wolf)
{
	int x;
	int y;
	int len;

	len = (wolf->stamina * 400) / 300;
	y = -1;
	while (++y < 10)
	{
		x = -1;
		while (++x < len)
			wolf->ml->img_data[(y + SCREEN_Y - 50) * SCREEN_X + SCREEN_X - 500 + x] = 0xFF00;
	}
}

int    ft_loop(t_wolf *wolf)
{

	struct timespec before;
	struct timespec after;
	clock_t	fps = 0;

	if (wolf->mode)
	{
		other_mode(wolf);
		return (1);
	}
	clock_gettime(CLOCK_MONOTONIC, &before);
	use_key(wolf);
	if (OS)
		usleep(1000);
	//fill_background(wolf);
	test_draw_no_par(wolf);
	//draw_all_screen(wolf);
	print_stamina(wolf);
	mlx_put_image_to_window(wolf->ml->mlx_ptr,
			wolf->ml->win_ptr, wolf->ml->img, 0, 0);
	clock_gettime(CLOCK_MONOTONIC, &after);
	fps = 1 / (double) (after.tv_sec - before.tv_sec + (after.tv_nsec - before.tv_nsec) / 1000000000.);
	show_fps(wolf, (int)fps);
	//	ft_printf("FPS = %d\n", (int)fps);
	return (1);
}

char	*get_path(char *name)
{
	int n;
	int ret;

	ret = 0;
	n = -1;
	while (name[++n])
		if (name[n] == '/')
				ret = n;
	name[ret + 1] = 0;
	return (name);
}

int load_selected_pack(t_wolf *wolf)
{
	int n;

	if (!wolf->packs)
		return (!ft_dprintf(2, "no pack found\n"));
	if (!wolf->map->pack)
	{
		if (!load_pack(wolf, wolf->packs[0]))
			return (!ft_dprintf(2, "pack loading failed\n"));
		return (1);
	}
	n = -1;
	while (wolf->packs[++n].name && ft_strcmp(wolf->packs[n].name, wolf->map->pack))
		;
	if (!wolf->packs[n].name)
		return (!ft_dprintf(2, "the pack %s was not found\n", wolf->map->pack));
	if (!load_pack(wolf, wolf->packs[n]))
			return (!ft_dprintf(2, "pack loading failed\n"));
	return (1);
}

int  init_pack_menu(t_wolf *wolf)
{
	int n;
	int m;
	t_image image;

	n = -1;
	while (wolf->packs[++n].name)
		;
	wolf->menu.pack.nb = n;
	wolf->menu.pack.name_size.w = PACK_NAME_W;
	wolf->menu.pack.name_size.h = PACK_NAME_H;
	wolf->menu.pack.nb_start = 0;
	wolf->menu.pack.delta = PACK_NAME_H + 10;
	wolf->menu.pack.nb_max = (SELECT_ZONE_H * 0.8 + 10) / wolf->menu.pack.delta;
	if (wolf->menu.pack.nb < wolf->menu.pack.nb_max)
		wolf->menu.pack.nb_max = wolf->menu.pack.nb;
	wolf->menu.pack.start = ((SCREEN_Y - SELECT_ZONE_H) / 2) + SELECT_ZONE_H * 0.1 + (SELECT_ZONE_H * 0.8
		- wolf->menu.pack.nb_max * wolf->menu.pack.delta + 10) / 2;
	if (!(wolf->menu.pack.name = ft_memalloc(sizeof(int*) * wolf->menu.pack.nb)))
		return (0);
	n = -1;
	while (++n < wolf->menu.pack.nb)
	{
		if (!(image.img = mlx_xpm_file_to_image(wolf->ml->mlx_ptr, wolf->packs[n].image, &image.w, &image.h)))
			return (0);
		if (!(image.data = (int*)mlx_get_data_addr(image.img, &wolf->ml->bits_per_pixel, &wolf->ml->size_line, &wolf->ml->endian)))
                        return (0);
		if (!(wolf->menu.pack.name[n] = ft_memalloc(sizeof(int) * (PACK_NAME_W * PACK_NAME_H))))
                	return (0);
		m = -1;
		while (++m < PACK_NAME_W * PACK_NAME_H && m < image.w * image.h)
			wolf->menu.pack.name[n][m] = image.data[m];
		mlx_destroy_image(wolf->ml->mlx_ptr, image.img);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_wolf        *wolf; //pleaaaase; static // nope, stackoverflow
	t_mlx_struct    ml;

	if (!(wolf = ft_memalloc(sizeof(t_wolf)))) ///// pffffffffffffff
		return (-1);
	if (ac > 1)
	{
		if (!ft_get_map(wolf, av[1]))
			return (-1);
		if (!init_mlx(&ml))
			return (-1);
		wolf->ml = &ml;
		wolf->path = get_path(av[0]);
		get_all_packs(wolf);
		if (!load_selected_pack(wolf))
			return (-1);
		init_pack_menu(wolf);

//		if (!wolf->packs || !load_pack(wolf, wolf->packs[0]))
//			return (-1);
		init_key(wolf);
		init_button(wolf);
	}
	else
		return (-1);
	t_vector2 tmp = init_vector2(0, -1);
	wolf->dir = tmp;
	wolf->dir_angle = -90;
	wolf->fov = 45.;
	wolf->pos.x += EPSILON;
	wolf->pos.y += EPSILON;
	mlx_loop_hook(ml.mlx_ptr, ft_loop, wolf);
	mlx_hook(ml.win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_destroy, wolf);
	mlx_hook(ml.win_ptr, KEYPRESS, KEYPRESSMASK, deal_key_down, wolf);
	mlx_hook(ml.win_ptr, KEYRELEASE, KEYRELEASEMASK,deal_key_up, wolf);
	mlx_hook(ml.win_ptr, BUTTONPRESS, BUTTONPRESSMASK,deal_button, wolf);
	mlx_hook(ml.win_ptr, BUTTONRELEASE, BUTTONRELEASEMASK,deal_button_release, wolf);
	mlx_hook(ml.win_ptr, MOTIONNOTIFY, POINTERMOTIONMASK,deal_motion, wolf);
	mlx_loop(ml.mlx_ptr);
	return (0);
}
