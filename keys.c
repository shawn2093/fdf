/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:58:35 by long              #+#    #+#             */
/*   Updated: 2024/01/27 17:23:53 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mlx_close(t_fdf **fdf)
{
	mlx_destroy_window((*fdf)->mlx, (*fdf)->win);
	exit(EXIT_SUCCESS);
	return (0);
}

void	handle_nums(int key, t_fdf **fdf)
{
	if (key == ONE_KEY && (*fdf)->palette_type >= 1 && (*fdf)->print_flat == 0)
		(*fdf)->palette_idx = 0;
	if (key == TWO_KEY && (*fdf)->palette_type >= 2 && (*fdf)->print_alt == 0)
		(*fdf)->palette_idx = 1;
	if (key == THREE_KEY && (*fdf)->palette_type >= 3)
		(*fdf)->palette_idx = 2;
	if (key == FOUR_KEY && (*fdf)->palette_type >= 4)
		(*fdf)->palette_idx = 3;
	if (key == FIVE_KEY && (*fdf)->palette_type >= 5)
		(*fdf)->palette_idx = 4;
	if (key == SIX_KEY && (*fdf)->palette_type >= 6)
		(*fdf)->palette_idx = 5;
	if (key == SEVEN_KEY && (*fdf)->palette_type >= 7)
		(*fdf)->palette_idx = 6;
	if (key == EIGHT_KEY && (*fdf)->palette_type >= 8)
		(*fdf)->palette_idx = 7;
	if (key == NINE_KEY && (*fdf)->palette_type >= 9)
		(*fdf)->palette_idx = 8;
	if (key == ZERO_KEY && (*fdf)->palette_type >= 10)
		(*fdf)->palette_idx = 9;
}

void	handle_orientation(int key, t_fdf **fdf)
{
	if (key == PLUS_KEY)
		(*fdf)->scale += 1;
	if (key == MINUS_KEY && (*fdf)->scale > 0)
		(*fdf)->scale -= 1;
	if (key == LEFT_BRACKET_KEY)
		(*fdf)->scale_z -= 1;
	if (key == RIGHT_BRACKET_KEY)
		(*fdf)->scale_z += 1;
	if (key == A_KEY)
		(*fdf)->angle_x -= 0.1;
	if (key == D_KEY)
		(*fdf)->angle_x += 0.1;
	if (key == W_KEY)
		(*fdf)->angle_y -= 0.1;
	if (key == S_KEY)
		(*fdf)->angle_y += 0.1;
	if (key == Q_KEY)
		(*fdf)->angle_z -= 0.1;
	if (key == E_KEY)
		(*fdf)->angle_z += 0.1;
	if (key == Z_KEY)
		(*fdf)->angle -= 0.1;
	if (key == X_KEY)
		(*fdf)->angle += 0.1;
}

void	handle_colornmove(int key, t_fdf **fdf)
{
	if (key == LEFT_KEY)
		(*fdf)->move_x -= 10;
	if (key == RIGHT_KEY)
		(*fdf)->move_x += 10;
	if (key == UP_KEY)
		(*fdf)->move_y -= 10;
	if (key == DOWN_KEY)
		(*fdf)->move_y += 10;
	if (key == BACKSLASH_KEY)
		(*fdf)->palette_sign *= -1;
	if (key == R_KEY)
		update_color((*fdf)->palette_update[(*fdf)->palette_idx], 'r', fdf);
	if (key == G_KEY)
		update_color((*fdf)->palette_update[(*fdf)->palette_idx], 'g', fdf);
	if (key == B_KEY)
		update_color((*fdf)->palette_update[(*fdf)->palette_idx], 'b', fdf);
	if (key == T_KEY)
		update_color((*fdf)->palette_update[(*fdf)->palette_idx], 't', fdf);
	if (key == ENTER_KEY)
		invert_color((*fdf)->palette_update[(*fdf)->palette_idx], fdf);
}

int	handle_keys(int key, t_fdf **fdf)
{
	if (key == I_KEY)
		(*fdf)->projection = 'i';
	if (key == C_KEY)
		(*fdf)->projection = 'c';
	if (key == O_KEY)
		(*fdf)->projection = 'o';
	if (key == SPACE_KEY)
		init_fdf(fdf);
	if (key == ESC_KEY)
		mlx_close(fdf);
	handle_nums(key, fdf);
	handle_orientation(key, fdf);
	handle_colornmove(key, fdf);
	mlx_clear_window((*fdf)->mlx, (*fdf)->win);
	draw(*fdf);
	return (0);
}
