/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_pack_info.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/18 14:21:42 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/15 16:21:55 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

int get_info(int fd, char **line, t_info *info)
{
	char *tmp;

	while (get_next_line(fd, line) == 1)
	{
		remove_comment(*line);
		tmp = jump_space(*line);
		if (tmp[0])
		{
			if (!ft_strncmp(tmp, "number", 6))
			{
				if (info->nb || !(info->nb = get_nbr(&tmp[6])))
					return (ft_super_free(1, *line));
			}
			else if (!ft_strncmp(tmp, "file", 4))
			{
				if (info->file || !(info->file = get_str(&tmp[4])))
					return (ft_super_free(1, *line));
			}
			else if (!ft_strncmp(tmp, "length", 6))
			{
				if (info->len.w || !(info->len.w = get_nbr(&tmp[6])))
					return (ft_super_free(1, *line));
			}
			else if (!ft_strncmp(tmp, "height", 6))
			{
				if (info->len.h || !(info->len.h = get_nbr(&tmp[6])))
					return (ft_super_free(1, *line));
			}
			else
				return (1);
		}
		free(*line);
		*line = 0;
	}
	return (1);
}

int get_pack_info(char *file, t_pack *pack)
{
	int		fd;
	char	*line;

	ft_bzero(pack, sizeof(t_pack));
	pack->roof = -1;
	pack->floor = -1;
	pack->menu.background.color = -1;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (!ft_printf("Unable to read file %s\n", file));
	while (get_next_line(fd, &line) == 1)
	{
		remove_comment(line);
		if (!check_line(fd, line, pack))
		{
			free(line);
			close(fd);
			return (free_pack(pack));
		}
		free(line);
	}
	if (close(fd) == -1 || !check_pack(file, pack))
		return (free_pack(pack));
	return (1);
}

char *get_pack_conf(char *path)
{
	DIR				*dir;
	struct dirent	*info;
	char			*name;

	if (!path)
		return (0);
	name = 0;
	if (!(dir = opendir(path)))
		return (0);
	while ((info = readdir(dir)))
		if (info->d_type == DT_REG && ft_strlen(info->d_name) > 5 && !ft_strcmp(".conf", &info->d_name[ft_strlen(info->d_name) - 5]))
		{
			name = ft_super_join(3, path, "/", info->d_name);
			break ;
		}
	closedir(dir);
	free(path);
	return (name);
}

int	get_all_packs(t_wolf *wolf)
{
	DIR				*dir;
	struct dirent	*info;
	char			*path;
	char			*conf_path;
	t_pack			pack;

	if (!(path = ft_strjoin(wolf->path, TEXT_PACK_DIR)))
		return (0);
	if (!(dir = opendir(path)))
		return (0);
	free(path);
	while ((info = readdir(dir)))
		if (info->d_type == DT_DIR && ft_strcmp(".", info->d_name)
				&& ft_strcmp("..", info->d_name)
				&& (path = ft_super_join(3, wolf->path, TEXT_PACK_DIR, info->d_name)))
		{
			if ((conf_path = get_pack_conf(path)) && get_pack_info(conf_path, &pack))
				packs_realloc(wolf, pack);
			free(conf_path);
		}
	closedir(dir);
	if (wolf->packs && wolf->packs[0].name)
		ft_quicksort(wolf->packs, get_packs_len(wolf->packs) , sizeof(t_pack), pack_name_cmp);
	return (1);
}

/*
   int main(int ac, char **av)
   {
   t_pack pack;
   t_wolf wolf;
   int n;

   ft_bzero(&wolf, sizeof(t_wolf));						//faire d'autres test plus tard
   if (!get_pack_info(av[1], &pack))
   {
   ft_printf("invalid\n");
   return (0);
   }
   ft_printf("name = %s\n", pack.name);
   ft_printf("menu = %s\n", pack.menu);
   ft_printf("sky = %s\n", pack.skybox);
   ft_printf("roof = %X\n", pack.roof);
   ft_printf("floor = %X\n", pack.floor);
   ft_printf("text nb = %d\n", pack.texture.nb_textures);
   ft_printf("text file = %s\n", pack.texture.textures);
   ft_printf("text size w = %d h = %d\n", pack.texture.texture_size.w, pack.texture.texture_size.h);
   ft_printf("sprite file = %s\n", pack.sprite.sprites);
   ft_printf("button file = %s\n", pack.button.buttons);
   free_pack(&pack);
   get_all_packs(&wolf);
   if (wolf.packs)
   {
   n = -1;
   while (wolf.packs[++n].name)
   ft_putendl(wolf.packs[n].menu);
   n = -1;
   while (wolf.packs[++n].name)
   free_pack(&wolf.packs[n]);
   free(wolf.packs);
   }
   return (0);
   }*/
