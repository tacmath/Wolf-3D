/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils4.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 15:35:33 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 15:35:35 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

int packs_realloc(t_wolf *wolf, t_pack pack)
{
    int len;
    int n;
    t_pack *tmp;
    
    len = 0;
    while (wolf->packs && wolf->packs[len].name)
        len++;
    if (!(tmp = malloc(sizeof(t_pack) * (len + 2))))
        return (0);
    n = -1;
    while (++n < len)
        tmp[n] = wolf->packs[n];
    tmp[n] = pack;
    ft_bzero(&tmp[n + 1], sizeof(t_pack));
    free(wolf->packs);
    wolf->packs = tmp;
    return (1);
}

int pack_name_cmp(void *s1, void *s2)
{
    t_pack            *p1;
    t_pack            *p2;
    
    p1 = s1;
    p2 = s2;
    return (ft_strcmp(p1->name, p2->name));
}

static void    swap_mem(char *s1, char *s2, int size) //enlever quicksort plus tard
{
    char    tmp[size];
    int        n;
    
    n = -1;
    while (++n < size)
        tmp[n] = s1[n];
    n = -1;
    while (++n < size)
        s1[n] = s2[n];
    n = -1;
    while (++n < size)
        s2[n] = tmp[n];
}

void        ft_quicksort(void *tab, int len,
                                int type_size, int (*cmp)(void*, void*))
{
    char    *mem;
    char    *compa;
    int        n;
    int        m;
    
    if (len < 2)
        return ;
    mem = (char*)tab;
    compa = &mem[(len - 1) * type_size];
    m = 0;
    n = -1;
    while (++n < len)
        if (cmp(&mem[n * type_size], compa) <= 0)
        {
            if (m != n)
                swap_mem(&mem[n * type_size], &mem[m * type_size], type_size);
            m++;
        }
    ft_quicksort(mem, --m, type_size, cmp);
    ft_quicksort(&mem[m * type_size], len - m, type_size, cmp);
}

int get_packs_len(t_pack *packs)
{
    int len;
    
    len = -1;
    while (packs[++len].name)
        ;
    return (len);
}
