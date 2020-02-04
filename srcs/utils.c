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

t_block        *ft_get_nb(t_map *map, char *str, t_vector2 *pos)
{
    int        n;
    int        m;
    t_block     *line;
    
    if (!(line = ft_memalloc(sizeof(t_block) * map->map_size.x)))
        return (0);
    n = -1;
    m = -1;
    if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-' || str[0] == 'x')
        line[++m].type = ft_atoi(str); //need to check if no overflow
    if (str[0] == 'x')
        *pos = init_vector2(m + 0.5, map->map_size.y - 0.5);
    while (str[++n])
        if ((str[n] == ' ' || str[n] == '\t') && ((str[n + 1] >= '0'
                               && str[n + 1] <= '9') || str[n + 1] == '-' ||  str[n + 1] == 'x'))
        {
            line[++m].type = ft_atoi(&str[n]);
            if (str[n + 1] == 'x')
                *pos = init_vector2(m + 0.5, map->map_size.y - 0.5);
        }
    free(str);
    return (line);
}

int        ft_map_realloc(t_map *map, char *str, t_vector2 *pos)
{
    t_block    **tmp;
    int        n;
    
    if (!(tmp = malloc(sizeof(t_block*) * map->map_size.y)))
        return (0);
    n = -1;
    while (++n < map->map_size.y - 1)
        tmp[n] = map->map[n];
    free(map->map);
    if (!(tmp[n] = ft_get_nb(map, str, pos)))
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
