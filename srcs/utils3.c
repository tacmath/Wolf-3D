/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils3.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 15:33:08 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 15:33:23 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"
#include <unistd.h>

int  free_pack(t_pack *pack)
{
    free(pack->name);
    free(pack->skybox);
    free(pack->menu.menu);
    free(pack->menu.background.file);
    free(pack->texture.textures);
    free(pack->sprite.sprites);
    free(pack->button.buttons);
    get_next_line(0, 0);
    return (0);
}

int add_path_to_file(char *path, char **file)
{
    char *tmp;
    
    if (!(tmp = ft_strjoin(path, *file)))
        return (0);
    free(*file);
    *file = tmp;
    return (1);
}

int check_file(char *file, char *type)
{
    int file_len;
    int type_len;
    
    if (access(file, R_OK))
        return (0);
    file_len = ft_strlen(file);
    type_len = ft_strlen(type);
    if (file_len <= type_len + 1 || file[file_len - type_len - 1] != '.'
        || ft_strcmp(type, &file[file_len - type_len]))
        return (0);
    return (1);
}

static void    join_all_arg(int nb_arg, char *tmp, char **arg)
{
    int m;
    int n;
    int i;
    
    n = 0;
    i = -1;
    while (++i < nb_arg)
    {
        m = -1;
        while (arg[i][++m])
            tmp[n++] = arg[i][m];
    }
    tmp[n] = 0;
}

char        *ft_super_join(int nb_arg, ...)
{
    va_list    ap;
    char    *tmp;
    char    **arg;
    int        n;
    int        m;
    
    va_start(ap, nb_arg);
    if (!(arg = malloc(sizeof(char*) * nb_arg)))
        return (0);
    n = -1;
    while (++n < nb_arg)
        arg[n] = va_arg(ap, char*);
    va_end(ap);
    m = 0;
    n = -1;
    while (++n < nb_arg)
        m += ft_strlen(arg[n]);
    if (!(tmp = malloc(sizeof(char) * (m + 1))))
        return (0);
    join_all_arg(nb_arg, tmp, arg);
    free(arg);
    return (tmp);
}
