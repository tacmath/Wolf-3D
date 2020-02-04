/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_pack_check2.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 15:40:11 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 15:40:13 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

int check_head(char *line, t_pack *pack)
{
    if (!ft_strncmp(line, "name", 4))
    {
        if (pack->name || !(pack->name = get_str(&line[4])))
            return (0);
    }
    else if (!ft_strncmp(line, "skybox", 6))
    {
        if (pack->skybox || !(pack->skybox = get_str(&line[6])))
            return (0);
    }
    else if (!ft_strncmp(line, "pack", 4))
    {
        if (pack->image || !(pack->image = get_str(&line[4])))
            return (0);
    }
    else if (!ft_strncmp(line, "menu_background", 15))
    {
        if (ft_strchr(&line[15], '"'))
        {
            if (pack->menu.background.file || !(pack->menu.background.file = get_str(&line[15])))
                return (0);
        }
        else if (pack->menu.background.color != -1 || (pack->menu.background.color = get_nbr_hex(&line[15])) == -1)
            return (0);
    }
    else if (!ft_strncmp(line, "roof", 4))
    {
        if (pack->roof != -1 || (pack->roof = get_nbr_hex(&line[4])) == -1)
            return (0);
    }
    else if (!ft_strncmp(line, "floor", 5))
    {
        if (pack->floor != -1 || (pack->floor = get_nbr_hex(&line[5])) == -1)
            return (0);
    }
    else
        return (1);
    return (-1);
}

int check_line(int fd, char *line, t_pack *pack)
{
    int        ret;
    t_info    info;
    
    ft_bzero(&info, sizeof(t_info));
    if ((line = jump_space(line)) && !line[0])
        return (1);
    if (!(ret = check_head(line, pack)))
        return (0);
    else if (ret == -1)
        return (1);
    else if (!ft_strncmp(line, "[TEXTURE]", 9))
    {
        if (!get_info(fd, &line, &info) || !check_texture(pack, info) || !(ret = 3))
            return (ft_super_free(1, info.file));
    }
    else if (!ft_strncmp(line, "[SPRITE]", 8))
    {
        if (!get_info(fd, &line, &info) || !check_sprite(pack, info) || !(ret = 3))
            return (ft_super_free(1, info.file));
    }
    else if (!ft_strncmp(line, "[BUTTON]", 8))
    {
        if (!get_info(fd, &line, &info) || !check_button_info(pack, info) || !(ret = 3))
            return (ft_super_free(1, info.file));
    }
    else if (!ft_strncmp(line, "[MENU]", 6))
    {
        if (!get_info(fd, &line, &info) || !check_menu(pack, info) || !(ret = 3))
            return (ft_super_free(1, info.file));
    }
    else
        return (0);
    if (ret == 3 && line && (!check_line(fd, line, pack) || ft_super_free(1, line)))
        return (ft_super_free(1, line));
    return (1);
}

int check_pack(char *path, t_pack *pack)
{
    int n;
    int ret;
    
    if (!pack->name || pack->floor < 0 || pack->floor > 0xFFFFFF
        || pack->roof > 0xFFFFFF || (pack->roof < 0 && !pack->skybox)
        || (pack->roof > 0 && pack->skybox) || !pack->menu.menu
        || !pack->texture.textures || !pack->sprite.sprites
        || !pack->button.buttons || (pack->menu.background.color != -1
                                     && pack->menu.background.file) || (pack->menu.background.color == -1
                                                                        && !pack->menu.background.file) || !pack->image)
        return (0);
    ret = 0;
    n = -1;
    while (path[++n])
        if (path[n] == '/')
            ret = n;
    path[ret + 1] = 0;
    if ((pack->skybox && !add_path_to_file(path, &pack->skybox))
        || (pack->menu.background.file && !add_path_to_file(path, &pack->menu.background.file))
        || !add_path_to_file(path, &pack->menu.menu)
        || !add_path_to_file(path, &pack->texture.textures)
        || !add_path_to_file(path, &pack->sprite.sprites)
        || !add_path_to_file(path, &pack->button.buttons)
        || !add_path_to_file(path, &pack->image))
        return (0);
    if ((pack->skybox && !check_file(pack->skybox, "xpm"))
        || (pack->menu.background.file && !check_file(pack->menu.background.file, "xpm"))
        || !check_file(pack->menu.menu, "xpm")
        || !check_file(pack->texture.textures, "xpm")
        || !check_file(pack->sprite.sprites, "xpm")
        || !check_file(pack->button.buttons, "xpm")
        || !check_file(pack->image, "xpm"))
        return (0);
    return (1);
}
