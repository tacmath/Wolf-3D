/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtolower.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/30 14:57:06 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 14:59:35 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *s)
{
	int i;

	i = -1;
	while (s[++i] != '\0')
		s[i] = ft_tolower(s[i]);
	return (s);
}
