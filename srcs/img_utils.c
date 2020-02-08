#include "wolf.h"

unsigned int	*size_up(unsigned int *img_old, t_point old_size, double ratio)
{
	unsigned int	*new;
	t_point		new_size;
	double		incr_old;
	t_vector2	m;
	t_point		i;

	new_size = init_point(old_size.x * ratio, old_size.y * ratio);
	if (!(new = ft_memalloc(sizeof(unsigned int) * new_size.x * new_size.y)))
		return (NULL);
	incr_old = 1 / ratio;
	i.y = -1;
	m.y = 0;
	while (++i.y < new_size.y)
	{
		i.x = -1;
		m.x = 0;
		while (++i.x < new_size.x)
		{
			new[i.y * new_size.x + i.x] =
		img_old[(int)(((int)m.y) * old_size.x + m.x)];
			m.x += incr_old; 
		}
		m.y += incr_old;
	}
	return (new);
}

unsigned int	*size_down(unsigned int *img_old, t_point old_size, double ratio)
{
	unsigned int	*new;
	t_point		new_size;
	double		incr_new;
	t_vector2	m;
	t_point		i;

	new_size = init_point(old_size.x * ratio, old_size.y * ratio);
	if (!(new = ft_memalloc(sizeof(unsigned int) * new_size.x * new_size.y)))
		return (NULL);
	incr_new = ratio;
	i.y = -1;
	m.y = 0;
	while (++i.y < old_size.y)
	{
		i.x = -1;
		m.x = 0;
		while (++i.x < old_size.x)
		{
			new[(int)(((int)m.y) * new_size.x + m.x)] =
		img_old[i.y * old_size.x + i.x];
			m.x += incr_new; 
		}
		m.y += incr_new;
	}
	return (new);
}

unsigned int	*resize_img(unsigned int *img_old, t_point size_old, double ratio)
{
	if (ratio >= 1)
		return (size_up(img_old, size_old, ratio));
	else
		return (size_down(img_old, size_old, ratio));
}

unsigned int	*cut_img(unsigned int *img_old, t_point old_size, t_point start, t_point size)
{
	unsigned int	*new;
	int		i;
	int		j;

	if (start.x < 0 || start.y < 0 || start.x + size.x > old_size.x ||
	 start.y + size.y > old_size.y)
	 	return (NULL);
	 if (!(new = malloc(sizeof(unsigned int) * size.x * size.y)))
	 	return (NULL);
	 i = -1;

	 while (++i < size.y)
	 {
	 	j = -1;
	 	while (++j < size.x)
	 		new[i * size.x + j] =
	 			img_old[(start.y + i)* old_size.x + start.x + j];
	 }
	 return (new);
}
