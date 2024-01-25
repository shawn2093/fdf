/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:59:21 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:01:23 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_fdf **fdf)
{
	int	tmp_x;
	int	tmp_y;
	int	tmp_z;

	tmp_x = ((*fdf)->a).x;
	tmp_y = ((*fdf)->a).y * cos((*fdf)->angle_x) - ((*fdf)->a).z
		* sin((*fdf)->angle_x);
	tmp_z = ((*fdf)->a).y * sin((*fdf)->angle_x) + ((*fdf)->a).z
		* cos((*fdf)->angle_x);
	((*fdf)->a).x = tmp_x;
	((*fdf)->a).y = tmp_y;
	((*fdf)->a).z = tmp_z;
	tmp_x = ((*fdf)->b).x;
	tmp_y = ((*fdf)->b).y * cos((*fdf)->angle_x) - ((*fdf)->b).z
		* sin((*fdf)->angle_x);
	tmp_z = ((*fdf)->b).y * sin((*fdf)->angle_x) + ((*fdf)->b).z
		* cos((*fdf)->angle_x);
	((*fdf)->b).x = tmp_x;
	((*fdf)->b).y = tmp_y;
	((*fdf)->b).z = tmp_z;
}

void	rotate_y(t_fdf **fdf)
{
	int	tmp_x;
	int	tmp_y;
	int	tmp_z;

	tmp_x = ((*fdf)->a).x * cos((*fdf)->angle_y) + ((*fdf)->a).z
		* sin((*fdf)->angle_y);
	tmp_y = ((*fdf)->a).y;
	tmp_z = -((*fdf)->a).x * sin((*fdf)->angle_y) + ((*fdf)->a).z
		* cos((*fdf)->angle_y);
	((*fdf)->a).x = tmp_x;
	((*fdf)->a).y = tmp_y;
	((*fdf)->a).z = tmp_z;
	tmp_x = ((*fdf)->b).x * cos((*fdf)->angle_y) + ((*fdf)->b).z
		* sin((*fdf)->angle_y);
	tmp_y = ((*fdf)->b).y;
	tmp_z = -((*fdf)->b).x * sin((*fdf)->angle_y) + ((*fdf)->b).z
		* cos((*fdf)->angle_y);
	((*fdf)->b).x = tmp_x;
	((*fdf)->b).y = tmp_y;
	((*fdf)->b).z = tmp_z;
}

void	rotate_z(t_fdf **fdf)
{
	int	tmp_x;
	int	tmp_y;
	int	tmp_z;

	tmp_x = ((*fdf)->a).x * cos((*fdf)->angle_z) - ((*fdf)->a).y
		* sin((*fdf)->angle_z);
	tmp_y = ((*fdf)->a).x * sin((*fdf)->angle_z) + ((*fdf)->a).y
		* cos((*fdf)->angle_z);
	tmp_z = ((*fdf)->a).z;
	((*fdf)->a).x = tmp_x;
	((*fdf)->a).y = tmp_y;
	((*fdf)->a).z = tmp_z;
	tmp_x = ((*fdf)->b).x * cos((*fdf)->angle_z) - ((*fdf)->b).y
		* sin((*fdf)->angle_z);
	tmp_y = ((*fdf)->b).x * sin((*fdf)->angle_z) + ((*fdf)->b).y
		* cos((*fdf)->angle_z);
	tmp_z = ((*fdf)->b).z;
	((*fdf)->b).x = tmp_x;
	((*fdf)->b).y = tmp_y;
	((*fdf)->b).z = tmp_z;
}

void	update_color(int trgb, char c, t_fdf **fdf)
{
	int	t;
	int	r;
	int	g;
	int	b;
	int	tmp_t;

	tmp_t = (trgb >> 24) & 0xFF;
	r = (trgb >> 16) & 0xFF;
	g = (trgb >> 8) & 0xFF;
	b = trgb & 0xFF;
	t = tmp_t;
	if (c == 't')
		t += (*fdf)->palette_sign;
	else if (c == 'r')
		r = r + (*fdf)->palette_sign;
	else if (c == 'g')
		g = g + (*fdf)->palette_sign;
	else if (c == 'b')
		b = b + (*fdf)->palette_sign;
	(*fdf)->palette_update[(*fdf)->palette_idx]
		= (t << 24 | r << 16 | g << 8 | b);
}

void	invert_color(int trgb, t_fdf **fdf)
{
	int	neg;

	neg = (0xFFFFFF - trgb) | 0x00000000;
	(*fdf)->palette_update[(*fdf)->palette_idx] = neg;
}
