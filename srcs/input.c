/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/26 14:35:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 16:41:22 by mtaquet          ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int      ft_len(char *str)
{
	int             n;
	int             nb;

	nb = 0;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == 'x'
		|| (str[0] != 'o' && (str[1] >= '0' && str[1] <= '9'))
		|| (str[0] == 's' && str[1] == 'o'&& (str[2] >= '0' && str[2] <= '9')))
		nb++;
	n = 0;
	while (str[++n])
		if ((((str[n + 1] >= '0' && str[n + 1] <= '9') || str[n + 1] == 'x')
			|| (str[n + 1] == 'o' && str[n + 2] >= '0' && str[n + 2] <= '9')
                	|| (str[n + 1] == 's' && str[n + 2] == 'o' && str[n + 3] >= '0' && str[n + 3] <= '9'))
 			&& (str[n] == ' ' || str[n] == '\t'))
			nb++;
	return (nb);
}

static int		ft_check(t_map *map, char *str)
{
	int n;

	n = -1;
	while (str[++n])
		if ((str[n] < '0' || str[n] > '9') && str[n] != ' ' && str[n] != '\t'
			&& str[n] != 'x' && !(str[n] == 'o' && str[n + 1] >= '0' && str[n + 1] <= '9')
			&& !(str[n] == 's' && str[n + 1] == 'o' && str[n + 2] >= '0' && str[n + 2] <= '9'))
		{
			n = -1;
			while (++n < map->map_size.y - 1)
				free(map->map[n]);
			free(map->map);
			return (error_msg("Found wrong caracter. Exiting."));
		}
	n = -1;
	if (ft_len(str) != map->map_size.x)
	{
		n = -1;
		while (++n < map->map_size.y - 1)
			free(map->map[n]);
		free(map->map);					//free les ajout
		ft_putendl("test");
		return (error_msg("Found wrong line length. Exiting."));
	}
	return (1);
}

int init_map_info(int fd, t_wolf *wolf)
{
	char *line;
	char *tmp;
	t_map *map;

	map = wolf->map;
	while (get_next_line(fd, &line) == 1 && remove_comment(line))
	{	
		tmp = jump_space(line);
		if (tmp[0])
		{
			if (!ft_strncmp(tmp, "Pack", 4))
			{
					if (map->pack != 0 || !(map->pack = get_str(&tmp[4])))
						return (ft_super_free(1, line));
			}
			else
			{			
				if (!(map->map_size.x = ft_len(line)))
					return (error_msg("Found wrong line length. Exiting."));
				map->map_size.y++;
				if (!ft_check(map, line))
					return (0);
				if (!(map->map = malloc(sizeof(t_block*))))
					return (0);
				if (!(map->map[0] = ft_get_nb(line, wolf)))
					return (0);
				return (1);
			}
		}
		free(line);
	}
	return (1);
}

static int		ft_get_all(int fd, t_wolf *wolf)
{
	char	*line;

	if (!init_map_info(fd, wolf))
		return (0);
	while (get_next_line(fd, &line) == 1 && remove_comment(line))
	{
		wolf->map->map_size.y++;
		if (!ft_check(wolf->map, line))
			return (0);
		if (!ft_map_realloc(line, wolf))
			return (0);
	}
	if (wolf->map->map_size.x == 0)
		return (0);
	return (1);
}

int		ft_get_map(t_wolf *wolf, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1 || read(fd, 0, 0) == -1)
	{
		ft_putstr("No file ");
		ft_putendl(file);
		return (0);
	}
	wolf->obj = 0;
	wolf->nb_obj = 0;
	if (!(wolf->map = ft_memalloc(sizeof(t_map)))
        || !ft_get_all(fd, wolf))
		return (0);
	if (close(fd) == -1)
	{
		ft_putstr("No file ");
		ft_putendl(file);
		return (0);
	}
/*	ft_printf("nb = %d \n", wolf->nb_obj);
	for (int n = 0; n < wolf->nb_obj; n++)
		ft_printf("id = %d, nb = %d x = %f y = %f\n", wolf->obj[n].sprites[0], wolf->obj[n].nb_sprites, wolf->obj[n].pos.x, wolf->obj[n].pos.y);*/ //enlever plus tard
	return (1);
}
