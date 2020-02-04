/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/11 15:30:32 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 15:55:37 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

char *get_str(char *str)
{
	char *tmp;

	if (str[0] != ' ' && str[0] != '\t')
		return (0);
	str = jump_space(str);
	if (str[0] != '"')
		return (0);
	str = &str[1];
	if (!(tmp = ft_strchr(str, '"')))
		return (0);
	tmp[0] = 0;
	tmp = jump_space(&tmp[1]);
	if (tmp[0] || !ft_strlen(str))
		return (0);
	if (!(tmp = ft_strdup(str)))
		return (0);
	return (tmp);
}

int get_nbr(char *str)
{
	int n;
	int nb;

	if (str[0] != ' ' && str[0] != '\t')
		return (0);
	str = jump_space(str);
	if (!str[0])
		return (0);
	nb = ft_atoi(str);
	n = -1;
	while (str[++n] >= '0' && str[n] <= '9')
		;
	str = jump_space(&str[n]);
	if (str[0])
		return (0);

	return (nb);
}

static char hex_nb(char c)
{
	if (c <= '9' && c >= '0')
		return (c - '0');
	if (c <= 'F' && c >= 'A')
		return (c - 'A' + 10);
	if (c <= 'f' && c >= 'a')
		return (c - 'a' + 10);
	return (-1);
}

static int ft_atoi_base(char *str, char base)
{
	int	res;
	int	n;

	n = -1;
	res = 0;
	if (base > 10 && str[n + 1] == '0' && str[n + 2] == 'x')
		n += 2;
	while (hex_nb(str[++n]) < base && hex_nb(str[n]) != -1)
		res = res * base + hex_nb(str[n]);
	return (res);
}

int get_nbr_hex(char *str)
{
	int n;
	int nb;

	if (str[0] != ' ' && str[0] != '\t')
		return (-1);
	str = jump_space(str);
	if (!str[0])
		return (-1);
	if (str[0] == '0' && str[1] == 'x')
		str = &str[2];
	nb = ft_atoi_base(str, 16);				//changer par ft_atoi_base(str, 16)
	n = -1;
	while ((str[++n] >= '0' && str[n] <= '9') || (str[n] >= 'A' && str[n] <= 'F') || (str[n] >= 'a' && str[n] <= 'f'))
		;
	str = jump_space(&str[n]);
	if (str[0])
		return (-1);
	return (nb);
}
