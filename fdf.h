/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:09:42 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:22:23 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_KEY 126
# define DOWN_KEY 125
# define PLUS_KEY 24
# define MINUS_KEY 27
# define ESC_KEY 53
# define LEFT_BRACKET_KEY 33
# define RIGHT_BRACKET_KEY 30
# define A_KEY 0
# define D_KEY 2
# define W_KEY 13
# define S_KEY 1
# define Q_KEY 12
# define E_KEY 14
# define I_KEY 34
# define C_KEY 8
# define O_KEY 31
# define Z_KEY 6
# define X_KEY 7
# define R_KEY 15
# define G_KEY 5
# define B_KEY 11
# define T_KEY 17
# define SPACE_KEY 49
# define ONE_KEY 18
# define TWO_KEY 19
# define THREE_KEY 20
# define FOUR_KEY 21
# define FIVE_KEY 23
# define SIX_KEY 22
# define SEVEN_KEY 26
# define EIGHT_KEY 28
# define NINE_KEY 25
# define ZERO_KEY 29
# define BACKSLASH_KEY 42
# define ENTER_KEY 36
# define WIDTH 1920
# define HEIGHT 1080

# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"
# include <math.h>
# include <mlx.h>

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_bres
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		d;
	int		yi;
	int		xi;
}			t_bres;

typedef struct s_fdf
{
	void	*win;
	void	*mlx;
	t_point	**matrix;
	int		height;
	int		width;
	int		move_x;
	int		move_y;
	int		scale;
	int		scale_z;
	double	angle;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	int		projection;
	int		palette_idx;
	int		palette_type;
	int		palette_sign;
	int		palette_ori[10];
	int		palette_update[10];
	int		print_flat;
	int		print_alt;
	t_point	a;
	t_point	b;
	t_img	img;
}			t_fdf;

// utils_1.c
void		zoom(t_fdf **fdf);
void		isometric(t_fdf **fdf);
void		cabinet(t_fdf **fdf);
void		oblique(t_fdf **fdf);
void		move(t_fdf **fdf);

// utils_2.c
void		rotate_x(t_fdf **fdf);
void		rotate_y(t_fdf **fdf);
void		rotate_z(t_fdf **fdf);
void		update_color(int trgb, char c, t_fdf **fdf);
void		invert_color(int trgb, t_fdf **fdf);

// draw.c
void		print_string(int y, char *str, t_fdf *fdf, int input);
void		print_color(t_fdf *fdf, int *i);
void		menu(t_fdf *fdf);
void		draw_xy(t_fdf *fdf);
int			draw(t_fdf *fdf);

// keys.c
void		handle_nums(int key, t_fdf **fdf);
void		handle_orientation(int key, t_fdf **fdf);
void		handle_colornmove(int key, t_fdf **fdf);
int			handle_keys(int key, t_fdf **fdf);

// plot.c
void		img_pix_put(t_img *img, int x, int y, unsigned int color);
void		plotlinelow(t_fdf **fdf, t_point first, t_point second);
void		plotlinehigh(t_fdf **fdf, t_point first, t_point second);
void		plotlinechoice(t_fdf **fdf, int diff_x, int diff_y);
void		plotline(t_fdf **fdf);

// matrix.c
int			ft_atoh(const char *str);
void		check_flatnalt(t_fdf **fdf, int i, int j);
int			check_color(t_fdf **fdf, int *idx, int trgb);
void		fill_matrix(t_fdf **fdf, int i, int *idx, t_gnl_list *input);
void		do_matrix(t_fdf **fdf, t_gnl_list *input);

// fdf.c with main
void		init_fdf(t_fdf **fdf);
void		check_width(t_fdf **fdf, t_gnl_list *node);
void		read_map(int fd, t_gnl_list **input, t_fdf **fdf);
int			error_handle(int ac, char **av);

#endif