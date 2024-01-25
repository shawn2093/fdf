/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:59:16 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:00:37 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_fdf **fdf)
{
	((*fdf)->a).x = ((*fdf)->a).x * (*fdf)->scale;
	((*fdf)->a).y = ((*fdf)->a).y * (*fdf)->scale;
	((*fdf)->b).x = ((*fdf)->b).x * (*fdf)->scale;
	((*fdf)->b).y = ((*fdf)->b).y * (*fdf)->scale;
	((*fdf)->a).z = ((*fdf)->a).z * (*fdf)->scale_z;
	((*fdf)->b).z = ((*fdf)->b).z * (*fdf)->scale_z;
}

void	isometric(t_fdf **fdf)
{
	((*fdf)->a).x = (((*fdf)->a).x - ((*fdf)->a).y) * cos((*fdf)->angle);
	((*fdf)->a).y = (((*fdf)->a).x + ((*fdf)->a).y) * sin((*fdf)->angle)
		- ((*fdf)->a).z;
	((*fdf)->b).x = (((*fdf)->b).x - ((*fdf)->b).y) * cos((*fdf)->angle);
	((*fdf)->b).y = (((*fdf)->b).x + ((*fdf)->b).y) * sin((*fdf)->angle)
		- ((*fdf)->b).z;
}

// https://en.wikipedia.org/wiki/Oblique_projection#Cabinet_projection
void	cabinet(t_fdf **fdf)
{
	((*fdf)->a).x = ((*fdf)->a).x + ((*fdf)->a).z * cos((*fdf)->angle) * 0.5;
	((*fdf)->a).y = ((*fdf)->a).y + ((*fdf)->a).z * sin((*fdf)->angle) * 0.5;
	((*fdf)->b).x = ((*fdf)->b).x + ((*fdf)->b).z * cos((*fdf)->angle) * 0.5;
	((*fdf)->b).y = ((*fdf)->b).y + ((*fdf)->b).z * sin((*fdf)->angle) * 0.5;
}

// https://www.101computing.net/oblique-projection-formulas/
void	oblique(t_fdf **fdf)
{
	((*fdf)->a).x = ((*fdf)->a).x - ((*fdf)->a).z * cos((*fdf)->angle);
	((*fdf)->a).y = ((*fdf)->a).y - ((*fdf)->a).z * sin((*fdf)->angle);
	((*fdf)->b).x = ((*fdf)->b).x - ((*fdf)->b).z * cos((*fdf)->angle);
	((*fdf)->b).y = ((*fdf)->b).y - ((*fdf)->b).z * sin((*fdf)->angle);
}

void	move(t_fdf **fdf)
{
	((*fdf)->a).x = ((*fdf)->a).x + (*fdf)->move_x;
	((*fdf)->a).y = ((*fdf)->a).y + (*fdf)->move_y;
	((*fdf)->b).x = ((*fdf)->b).x + (*fdf)->move_x;
	((*fdf)->b).y = ((*fdf)->b).y + (*fdf)->move_y;
}
