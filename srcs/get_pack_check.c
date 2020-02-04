/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_pack_check.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 15:38:12 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 15:40:07 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

int check_texture(t_pack *pack, t_info info)
{
	if (!info.nb || !info.file || !info.len.w || !info.len.h)
		return (0);
	pack->texture.nb_textures = info.nb;
	pack->texture.textures = info.file;
	pack->texture.texture_size = info.len;
	return (1);
}

int check_sprite(t_pack *pack, t_info info)
{
	if (!info.nb || !info.file || !info.len.w || !info.len.h)
		return (0);
	pack->sprite.nb_sprites = info.nb;
	pack->sprite.sprites = info.file;
	pack->sprite.sprite_size = info.len;
	return (1);
}

int check_button_info(t_pack *pack, t_info info)
{
	if (info.nb || !info.file || !info.len.w || !info.len.h)
		return (0);
	pack->button.buttons = info.file;
	pack->button.button_size = info.len;
	return (1);
}

int check_menu(t_pack *pack, t_info info)
{
	if (info.nb || !info.file || !info.len.w || !info.len.h)
		return (0);
	pack->menu.menu = info.file;
	pack->menu.menu_size = info.len;
	return (1);
}
