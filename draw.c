/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:58:55 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:07:42 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_string(int y, char *str, t_fdf *fdf, int input)
{
	char	*full_str;
	char	*input_str;

	if (input == 'i')
		input_str = ft_strdup("i");
	else if (input == 'c')
		input_str = ft_strdup("c");
	else if (input == 'o')
		input_str = ft_strdup("o");
	else
		input_str = ft_itoa(input);
	full_str = ft_strjoin(str, input_str);
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (y * 15), 0x00ff00, full_str);
	free(input_str);
	free(full_str);
}

void	print_color(t_fdf *fdf, int *i)
{
	int	j;

	j = -1;
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++(*i) * 15), 0x00ff00, "");
	print_string(++(*i), "Target of Color (0-9): ", fdf, fdf->palette_idx + 1);
	print_string(++(*i), "Change of Color (\\): ", fdf, fdf->palette_sign);
	while (++j < fdf->palette_type)
	{
		if (!((j == 0 && fdf->print_flat == 1) || (j == 1
					&& fdf->print_alt == 1)))
		{
			print_string(++(*i), "Details of Color ", fdf, j + 1);
			print_string(++(*i), "Transparency: ", fdf,
				(fdf->palette_update[j] >> 24) & 0xFF);
			print_string(++(*i), "R-color: ", fdf,
				(fdf->palette_update[j] >> 16) & 0xFF);
			print_string(++(*i), "G-color: ", fdf,
				(fdf->palette_update[j] >> 8) & 0xFF);
			print_string(++(*i), "B-color: ", fdf,
				fdf->palette_update[j] & 0xFF);
		}
	}
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++(*i) * 15), 0x00ff00,
		"ENTER Key to Invert Color");
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++(*i) * 15), 0x00ff00, "");
}

void	menu(t_fdf *fdf)
{
	int	i;

	i = -1;
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00,
		"Arrow key to move");
	print_string(++i, "Position X: ", fdf, fdf->move_x);
	print_string(++i, "Position Y: ", fdf, fdf->move_y);
	print_string(++i, "A/D to rotate x: ", fdf, (int)(fdf->angle_x * 10));
	print_string(++i, "W/S to rotate y: ", fdf, (int)(fdf->angle_y * 10));
	print_string(++i, "Q/E to rotate z: ", fdf, (int)(fdf->angle_z * 10));
	print_string(++i, "Z/X to change angle: ", fdf, (int)(fdf->angle * 10));
	print_string(++i, "+/- to scale up/down: ", fdf, fdf->scale - 20);
	print_string(++i, "[/] to scale alt: ", fdf, fdf->scale_z);
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00,
		"I: isometric projection");
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00,
		"C: cabinet projection");
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00,
		"O: oblique projection");
	print_string(++i, "Current projection: ", fdf, fdf->projection);
	print_color(fdf, &i);
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00,
		"SPACE Key to Reset");
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00,
		"ESC Key to Exit");
}

void	draw_xy(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->height)
	{
		j = -1;
		while (++j < fdf->width)
		{
			if (i + 1 != fdf->height)
			{
				fdf->a = fdf->matrix[i][j];
				fdf->b = fdf->matrix[i + 1][j];
				plotLine(&fdf);
			}
			if (j + 1 != fdf->width)
			{
				fdf->a = fdf->matrix[i][j];
				fdf->b = fdf->matrix[i][j + 1];
				plotLine(&fdf);
			}
		}
	}
}

int	draw(t_fdf *fdf)
{
	fdf->img.mlx_img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.mlx_img, &(fdf->img.bpp),
			&(fdf->img.line_len), &(fdf->img.endian));
	mlx_clear_window(fdf->mlx, fdf->win);
	draw_xy(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.mlx_img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.mlx_img);
	menu(fdf);
	return (0);
}
