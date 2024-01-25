/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:59:11 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:23:54 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

// first.x < second.x
void	plotlinelow(t_fdf **fdf, t_point first, t_point second)
{
	t_bres	a;

	a.dx = second.x - first.x;
	a.dy = second.y - first.y;
	a.yi = 1;
	if (a.dy < 0)
		a.yi = -1;
	a.dy *= a.yi;
	a.d = (2 * a.dy) - a.dx;
	a.y = first.y;
	a.x = first.x - 1;
	while (++a.x <= second.x)
	{
		img_pix_put(&((*fdf)->img), a.x, a.y,
			(unsigned int)(*fdf)->palette_update[first.color]);
		if (a.d > 0)
		{
			a.y = a.y + a.yi;
			a.d = a.d + 2 * (a.dy - a.dx);
		}
		else
			a.d = a.d + 2 * a.dy;
	}
}

// first.y < second.y
void	plotlinehigh(t_fdf **fdf, t_point first, t_point second)
{
	t_bres	a;

	a.dx = second.x - first.x;
	a.dy = second.y - first.y;
	a.xi = 1;
	if (a.dx < 0)
		a.xi = -1;
	a.dx *= a.xi;
	a.d = (2 * a.dx) - a.dy;
	a.y = first.y - 1;
	a.x = first.x;
	while (++a.y <= second.y)
	{
		img_pix_put(&((*fdf)->img), a.x, a.y,
			(unsigned int)(*fdf)->palette_update[first.color]);
		if (a.d > 0)
		{
			a.x = a.x + a.xi;
			a.d = a.d + 2 * (a.dx - a.dy);
		}
		else
			a.d = a.d + 2 * a.dx;
	}
}

void	plotlinechoice(t_fdf **fdf, int diff_x, int diff_y)
{
	if (diff_y < diff_x)
	{
		if (((*fdf)->a).x > ((*fdf)->b).x)
			plotlinelow(fdf, ((*fdf)->b), (*fdf)->a);
		else
			plotlinelow(fdf, ((*fdf)->a), ((*fdf)->b));
	}
	else
	{
		if (((*fdf)->a).y > ((*fdf)->b).y)
			plotlinehigh(fdf, ((*fdf)->b), ((*fdf)->a));
		else
			plotlinehigh(fdf, ((*fdf)->a), ((*fdf)->b));
	}
}

void	plotline(t_fdf **fdf)
{
	int	diff_y;
	int	diff_x;

	zoom(fdf);
	rotate_x(fdf);
	rotate_y(fdf);
	rotate_z(fdf);
	if ((*fdf)->projection == 'i')
		isometric(fdf);
	else if ((*fdf)->projection == 'c')
		cabinet(fdf);
	else if ((*fdf)->projection == 'o')
		oblique(fdf);
	move(fdf);
	diff_y = ((*fdf)->b).y - ((*fdf)->a).y;
	diff_x = ((*fdf)->b).x - ((*fdf)->a).x;
	if (diff_y < 0)
		diff_y = -diff_y;
	if (diff_x < 0)
		diff_x = -diff_x;
	plotlinechoice(fdf, diff_x, diff_y);
}
