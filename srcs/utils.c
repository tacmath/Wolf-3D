/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 00:29:52 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 16:49:42 by mtaquet          ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

char *jump_space(char *str)
{
	int n;

	n = -1;
	while (str[++n] == ' ' || str[n] == '\t')
		;
	return (&str[n]);
}

int error_msg(char *error)
{
	ft_putendl(error);
	return (0);
}

int		add_obj(t_wolf *wolf, char *id, double x, double y)
{
	t_object *new;
	int n;

	if (!(new = malloc(sizeof(t_object) * (wolf->nb_obj + 1))))
		return (0);
	n = -1;
	while (++n < wolf->nb_obj)
		new[n] = wolf->obj[n];
	ft_bzero(&new[n], sizeof(t_object));
	if (!(new[n].sprites = malloc(sizeof(int))))
		return (0);
	new[n].sprites[0] = ft_atoi(id);
	new[n].nb_sprites = 1;
	new[n].pos.x = x;
	new[n].pos.y = y;
	free(wolf->obj);
	wolf->obj = new;
	wolf->nb_obj++;
	return (1);
}

t_block        *ft_get_nb(char *str, t_wolf *wolf)
{
	int        	n;
	int       	m;
	t_block     *line;
	t_map		*map;

	map = wolf->map;
	if (!(line = ft_memalloc(sizeof(t_block) * map->map_size.x)))
		return (0);
	n = -1;
	m = -1;
	if (str[0] >= '0' && str[0] <= '9')
		line[++m].type = ft_atoi(str); //need to check if no overflow
	else if (str[0] == 'x')
		wolf->pos = init_vector2(++m + 0.5, map->map_size.y - 0.5);
	else if (str[0] == 'o')
		add_obj(wolf, &str[1], ++m + 0.5, map->map_size.y - 0.5);
	else if (str[0] == 's' && str[1] == 'o')
	{
		line[++m].obj = 1;
		add_obj(wolf, &str[2], m + 0.5, map->map_size.y - 0.5);
	}
	while (str[++n])
		if (str[n] == ' ' || str[n] == '\t')
		{
			if (str[n + 1] >= '0' && str[n + 1] <= '9')
				line[++m].type = ft_atoi(&str[n + 1]); //need to check if no overflow
			else if(str[n + 1] == 'x')
				wolf->pos = init_vector2(++m + 0.5, map->map_size.y - 0.5);
			else if (str[n + 1] == 'o')
				add_obj(wolf, &str[n + 2], ++m + 0.5, map->map_size.y - 0.5);
			else if (str[n + 1] == 's' && str[n + 2] == 'o')
			{
				line[++m].obj = 1;
				add_obj(wolf, &str[n + 3], m + 0.5, map->map_size.y - 0.5);
			}
		}
	free(str);
	return (line);
}

int        ft_map_realloc(char *str, t_wolf *wolf)
{
	t_block    **tmp;
	t_map		*map;
	int        n;

	map = wolf->map;
	if (!(tmp = malloc(sizeof(t_block*) * map->map_size.y)))
		return (0);
	n = -1;
	while (++n < map->map_size.y - 1)
		tmp[n] = map->map[n];
	free(map->map);
	if (!(tmp[n] = ft_get_nb(str, wolf)))
		return (0);
	map->map = tmp;
	return (1);
}

int    remove_comment(char *line)
{
	char *tmp;

	if ((tmp = ft_strchr(line, '#')))
		tmp[0] = 0;
	return (1);
}
