
#include "wolf.h"

void init_key(t_wolf *wolf)
{
	wolf->key_used[FORWARD] = UP_KEY;
	wolf->key_used[BACKWARD] = DOWN_KEY;
	wolf->key_used[LOOK_L] = TURNL_KEY;
	wolf->key_used[LOOK_R] = TURNR_KEY;
	wolf->key_used[MOVE_L] = LEFT_KEY;
	wolf->key_used[MOVE_R] = RIGHT_KEY;;
	wolf->key_used[SPRINGT] = SHIFT_KEY;
}

int init_mlx(t_mlx_struct *ml)
{
	if (!(ml->mlx_ptr = mlx_init()))
		return (0);
	if (!(ml->win_ptr = mlx_new_window(ml->mlx_ptr, SCREEN_X, SCREEN_Y, "WOLF 3D")))
		return (0);
	if (!(ml->img = mlx_new_image(ml->mlx_ptr, SCREEN_X, SCREEN_Y)))
		return (0);
	if (!(ml->img_data = (int*)mlx_get_data_addr(ml->img,
					&ml->bits_per_pixel, &ml->size_line, &ml->endian)))
		return (0);
	ml->nb_pxl = SCREEN_X * SCREEN_Y;
	return (1);
}

static void get_texture(unsigned int **texture, t_image planche, t_rect src)
{
	int x;
	int y;
	int start;

	start = src.x + src.y * planche.w;
	x = -1;
	while (++x < src.w)
	{
		y = -1;
		while (++y < src.h)
			texture[x][y] = planche.data[start + x + y * planche.w];
	}
}

static void get_normal_texture(unsigned int *texture, t_image planche, t_rect src)
{
	int x;
	int y;
	int start;

	start = src.x + src.y * planche.w;
	x = -1;
	while (++x < src.w)
	{
		y = -1;
		while (++y < src.h)
			texture[x + src.w * y] = planche.data[start + x + y * planche.w];
	}
}

static int init_textures(t_wolf *wolf)
{
	int n;
	int m;

	if (!(wolf->textures = ft_memalloc(sizeof(int***) * wolf->nb_textures)))
		return (0);
	n = -1;
	while (++n < wolf->nb_textures)
	{
		if (!(wolf->textures[n] = ft_memalloc(sizeof(int**) * 2)))
                	return (0);
		if (!(wolf->textures[n][0] = ft_memalloc(sizeof(int*) * wolf->texture_size.w)))
			return (0);
		if (!(wolf->textures[n][1] = ft_memalloc(sizeof(int*) * wolf->texture_size.w)))
			return (0);
		m = -1;
		while (++m < wolf->texture_size.w)
		{
			if (!(wolf->textures[n][0][m] = ft_memalloc(sizeof(int) * wolf->texture_size.h)))
				return (0);
			if (!(wolf->textures[n][1][m] = ft_memalloc(sizeof(int) * wolf->texture_size.h)))
				return (0);
		}
	}
	return (1);
}

static int init_sprite(t_wolf *wolf)
{
	int n;
	int m;

	if (!(wolf->sprites = ft_memalloc(sizeof(int**) * wolf->nb_sprites)))
		return (0);
	n = -1;
	while (++n < wolf->nb_sprites)
	{
		if (!(wolf->sprites[n] = ft_memalloc(sizeof(int*) * wolf->sprites_size.w)))
			return (0);
		m = -1;
		while (++m < wolf->sprites_size.w)
		{
			if (!(wolf->sprites[n][m] = ft_memalloc(sizeof(int) * wolf->sprites_size.h)))
				return (0);
		}
	}
	return (1);
}

int get_all_textures(t_wolf *wolf, t_texture texture)
{
	t_image	planche;
	t_rect	src;
	char	id;

	if (!(planche.img = mlx_xpm_file_to_image(wolf->ml->mlx_ptr, texture.textures, &planche.w, &planche.h)))
		return (0);
	if (!(planche.data = (int*)mlx_get_data_addr(planche.img,
					&wolf->ml->bits_per_pixel, &wolf->ml->size_line, &wolf->ml->endian)))
		return (0);
	src.y = 0;
	src.w = texture.texture_size.w;
	src.h = texture.texture_size.h;
	if (!init_textures(wolf))
		return (0);
	id = 1;
	while (src.y + src.h  <= planche.h)
	{
		src.x = 0;
		while (src.x + src.w * 2 <= planche.w && id < texture.nb_textures)
		{
			get_texture(wolf->textures[(int)id][0], planche, src);
			src.x += src.w;
			get_texture(wolf->textures[(int)id][1], planche, src);
			id++;
			src.x += src.w;
		}
		src.y += src.h;
	}
	mlx_destroy_image(wolf->ml->mlx_ptr, planche.img);
	return (1);
}

int get_all_sprites(t_wolf *wolf, t_sprite sprite)
{
	t_image	planche;
	t_rect	src;
	char	id;

	if (!(planche.img = mlx_xpm_file_to_image(wolf->ml->mlx_ptr, sprite.sprites, &planche.w, &planche.h)))
		return (0);
	if (!(planche.data = (int*)mlx_get_data_addr(planche.img,
					&wolf->ml->bits_per_pixel, &wolf->ml->size_line, &wolf->ml->endian)))
		return (0);
	src.y = 0;
	src.w = sprite.sprite_size.w;
	src.h = sprite.sprite_size.h;
	if (!init_sprite(wolf))
		return (0);
	id = 0;
	while (src.y + src.h  <= planche.h)
	{
		src.x = 0;
		while (src.x + src.w <= planche.w && id < sprite.nb_sprites)
		{
			get_texture(wolf->sprites[(int)(id++)], planche, src);
			src.x += src.w;
		}
		src.y += src.h;
	}
	mlx_destroy_image(wolf->ml->mlx_ptr, planche.img);
	return (1);
}

int load_menu(t_wolf *wolf, t_menu_info menu)
{
	t_image	planche;
	t_rect	src;
	int		n;

	if (!(planche.img = mlx_xpm_file_to_image(wolf->ml->mlx_ptr, menu.menu, &planche.w, &planche.h)))
		return (0);
	if (!(planche.data = (int*)mlx_get_data_addr(planche.img,
					&wolf->ml->bits_per_pixel, &wolf->ml->size_line, &wolf->ml->endian)))
		return (0);
	src.y = 0;
	src.w = menu.menu_size.w;
	src.h = menu.menu_size.h;
	n = -1;
	while (++n < 4)
		if (!(wolf->menu.menu[n] = ft_memalloc(sizeof(int) * (src.w * src.h))))
			return (0);
	n = -1;
	while (src.y + src.h  <= planche.h)
	{
		src.x = 0;
		while (src.x + src.w <= planche.w && ++n < 4)
		{
			get_normal_texture(wolf->menu.menu[n], planche, src);
			src.x += src.w;
		}
		src.y += src.h;
	}
	mlx_destroy_image(wolf->ml->mlx_ptr, planche.img);
	if (menu.background.file)
	{
		if (!(planche.img = mlx_xpm_file_to_image(wolf->ml->mlx_ptr, menu.background.file, &planche.w, &planche.h)))
			return (0);
		if (!(planche.data = (int*)mlx_get_data_addr(planche.img,
					&wolf->ml->bits_per_pixel, &wolf->ml->size_line, &wolf->ml->endian)))
			return (0);
		if (!(wolf->menu.background = ft_memalloc(sizeof(int) * (SCREEN_X * SCREEN_Y))))
			return (0);
		n = -1;
		while (++n < planche.w * planche.h)
			wolf->menu.background[n] = planche.data[n];
		mlx_destroy_image(wolf->ml->mlx_ptr, planche.img);
	}
	return (1);
}

int load_buttons(t_wolf *wolf, t_button_pack button)
{
	t_image	planche;
	t_rect	src;
	int		n;

	if (!(planche.img = mlx_xpm_file_to_image(wolf->ml->mlx_ptr, button.buttons, &planche.w, &planche.h)))
		return (0);
	if (!(planche.data = (int*)mlx_get_data_addr(planche.img,
					&wolf->ml->bits_per_pixel, &wolf->ml->size_line, &wolf->ml->endian)))
		return (0);
	src.y = 0;
	src.w = button.button_size.w;
	src.h = button.button_size.h;
	n = -1;
	while (++n < 5)
		if (!(wolf->menu.button[n][0] = ft_memalloc(sizeof(int) * (src.w * src.h)))
			|| !(wolf->menu.button[n][1] = ft_memalloc(sizeof(int) * (src.w * src.h))))
			return (0);
	n = 0;
	while (src.y + src.h <= planche.h)
	{
		src.x = 0;
		while (src.x + src.w * 2 <= planche.w && n < 5)
		{
			get_normal_texture(wolf->menu.button[n][0], planche, src);
			src.x += src.w;
			get_normal_texture(wolf->menu.button[n++][1], planche, src);
			src.x += src.w;
		}
		src.y += src.h;
	}
	mlx_destroy_image(wolf->ml->mlx_ptr, planche.img);
	return (1);
}

int get_skybox(t_wolf *wolf, char *file)
{
	t_image	skybox;
	int n;

	if (!(skybox.img = mlx_xpm_file_to_image(wolf->ml->mlx_ptr, file, &skybox.w, &skybox.h)))
		return (0);
	if (!(skybox.data = (int*)mlx_get_data_addr(skybox.img,
					&wolf->ml->bits_per_pixel, &wolf->ml->size_line, &wolf->ml->endian)))
		return (0);
	if (!(wolf->skybox = malloc(sizeof(int) * skybox.w * skybox.h)))
		return (0);
	n = -1;
	while (++n < skybox.w * skybox.h)
		wolf->skybox[n] = skybox.data[n];
	wolf->skybox_size.w = skybox.w;
	wolf->skybox_size.h = skybox.h;
	mlx_destroy_image(wolf->ml->mlx_ptr, skybox.img);
	return (1);
}

int load_pack(t_wolf *wolf, t_pack pack)
{
	wolf->roof = pack.roof;	
	if (pack.skybox != 0)
	{
		if (!get_skybox(wolf, pack.skybox))
			return (0);
	}
	else
		wolf->skybox = 0;
	wolf->floor = pack.floor;
	wolf->nb_textures = pack.texture.nb_textures + 1;
	wolf->nb_sprites = pack.sprite.nb_sprites;
	wolf->texture_size = pack.texture.texture_size;
	wolf->sprites_size = pack.sprite.sprite_size;
	wolf->menu.menu_size = pack.menu.menu_size;
	wolf->menu.background_color = pack.menu.background.color;
	wolf->menu.background = 0;
	wolf->menu.menu_size = pack.menu.menu_size;
	wolf->menu.button_size = pack.button.button_size;
	if (!(load_menu(wolf, pack.menu)))
		return (0);
	if (!load_buttons(wolf, pack.button))
		return (0);
	if (!get_all_textures(wolf, pack.texture))
		return (0);
	if (!get_all_sprites(wolf, pack.sprite))
		return (0);
	return (1);
}
