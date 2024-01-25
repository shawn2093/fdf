// #include <mlx.h>
#include "mlx/minilibx_macos/mlx.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include <math.h>
#include "fdf.h"

#define WIDTH 1920
#define HEIGHT 1080

int	ft_atoh(const char *str)
{
	int	minus_num;
	int	res;

	minus_num = 1;
	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus_num *= -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F'))
	{
		if (*str >= '0' && *str <= '9')
			res = res * 16 + *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			res = res * 16 + *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			res = res * 16 + *str - 'A' + 10;
		str++;
	}
	return (res * minus_num);
}

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
void plotLineLow(t_fdf **fdf, t_point first, t_point second)
{
	t_bres	a;

	a.dx = second.x - first.x;
	a.dy = second.y - first.y;
	a.yi = 1;
	if (a.dy < 0)
		a.yi = -1;
	a.dy = ABS(a.dy);
	a.D = (2 * a.dy) - a.dx;
	a.y = first.y;
	a.x = first.x - 1;
	while (++a.x <= second.x)
	{
		img_pix_put(&((*fdf)->img), a.x, a.y, (unsigned int) (*fdf)->palette_update[first.color]);
		if (a.D > 0)
		{
			a.y = a.y + a.yi;
			a.D = a.D + 2 * (a.dy - a.dx);
		}
		else
			a.D = a.D + 2 * a.dy;
	}
}

//first.y < second.y
void plotLineHigh(t_fdf **fdf, t_point first, t_point second)
{
	t_bres	a;

	a.dx = second.x - first.x;
	a.dy = second.y - first.y;
	a.xi = 1;
	if (a.dx < 0)
		a.xi = -1;
	a.dx = ABS(a.dx);
	a.D = (2 * a.dx) - a.dy;
	a.y = first.y - 1;
	a.x = first.x;
	while (++a.y <= second.y)
	{
		img_pix_put(&((*fdf)->img), a.x, a.y, (unsigned int) (*fdf)->palette_update[first.color]);
		if (a.D > 0)
		{
			a.x = a.x + a.xi;
			a.D = a.D + 2 * (a.dx - a.dy);
		}
		else
			a.D = a.D + 2 * a.dx;
	}
}

void zoom(t_fdf **fdf)
{
	((*fdf)->a).x = ((*fdf)->a).x * (*fdf)->scale;
	((*fdf)->a).y = ((*fdf)->a).y * (*fdf)->scale;
	((*fdf)->b).x = ((*fdf)->b).x * (*fdf)->scale;
	((*fdf)->b).y = ((*fdf)->b).y * (*fdf)->scale;
	((*fdf)->a).z = ((*fdf)->a).z * (*fdf)->scale_z;
	((*fdf)->b).z = ((*fdf)->b).z * (*fdf)->scale_z;
}
void isometric(t_fdf **fdf)
{
	((*fdf)->a).x = (((*fdf)->a).x - ((*fdf)->a).y) * cos((*fdf)->angle);
	((*fdf)->a).y = (((*fdf)->a).x + ((*fdf)->a).y) * sin((*fdf)->angle) - ((*fdf)->a).z;
	((*fdf)->b).x = (((*fdf)->b).x - ((*fdf)->b).y) * cos((*fdf)->angle);
	((*fdf)->b).y = (((*fdf)->b).x + ((*fdf)->b).y) * sin((*fdf)->angle) - ((*fdf)->b).z;
}
// https://en.wikipedia.org/wiki/Oblique_projection#Cabinet_projection
void cabinet(t_fdf **fdf)
{
	((*fdf)->a).x = ((*fdf)->a).x + ((*fdf)->a).z * cos((*fdf)->angle) * 0.5;
	((*fdf)->a).y = ((*fdf)->a).y + ((*fdf)->a).z * sin((*fdf)->angle) * 0.5;
	((*fdf)->b).x = ((*fdf)->b).x + ((*fdf)->b).z * cos((*fdf)->angle) * 0.5;
	((*fdf)->b).y = ((*fdf)->b).y + ((*fdf)->b).z * sin((*fdf)->angle) * 0.5;
}

// https://www.101computing.net/oblique-projection-formulas/
void oblique(t_fdf **fdf)
{
	((*fdf)->a).x = ((*fdf)->a).x - ((*fdf)->a).z * cos((*fdf)->angle);
	((*fdf)->a).y = ((*fdf)->a).y - ((*fdf)->a).z * sin((*fdf)->angle);
	((*fdf)->b).x = ((*fdf)->b).x - ((*fdf)->b).z * cos((*fdf)->angle);
	((*fdf)->b).y = ((*fdf)->b).y - ((*fdf)->b).z * sin((*fdf)->angle);
}

void move(t_fdf **fdf)
{
	((*fdf)->a).x = ((*fdf)->a).x + (*fdf)->move_x;
	((*fdf)->a).y = ((*fdf)->a).y + (*fdf)->move_y;
	((*fdf)->b).x = ((*fdf)->b).x + (*fdf)->move_x;
	((*fdf)->b).y = ((*fdf)->b).y + (*fdf)->move_y;
}

void rotate_x(t_fdf **fdf)
{
	int	tmp_x;
	int	tmp_y;
	int	tmp_z;

	tmp_x = ((*fdf)->a).x;
	tmp_y = ((*fdf)->a).y * cos((*fdf)->angle_x) - ((*fdf)->a).z * sin((*fdf)->angle_x);
	tmp_z = ((*fdf)->a).y * sin((*fdf)->angle_x) + ((*fdf)->a).z * cos((*fdf)->angle_x);
	((*fdf)->a).x = tmp_x;
	((*fdf)->a).y = tmp_y;
	((*fdf)->a).z = tmp_z;
	tmp_x = ((*fdf)->b).x;
	tmp_y = ((*fdf)->b).y * cos((*fdf)->angle_x) - ((*fdf)->b).z * sin((*fdf)->angle_x);
	tmp_z = ((*fdf)->b).y * sin((*fdf)->angle_x) + ((*fdf)->b).z * cos((*fdf)->angle_x);
	((*fdf)->b).x = tmp_x;
	((*fdf)->b).y = tmp_y;
	((*fdf)->b).z = tmp_z;
	// ((*fdf)->a).y = ((*fdf)->a).y * cos((*fdf)->angle_x) - ((*fdf)->a).z * sin((*fdf)->angle_x);
	// ((*fdf)->b).y = ((*fdf)->b).y * cos((*fdf)->angle_x) - ((*fdf)->b).z * sin((*fdf)->angle_x);
}

void rotate_y(t_fdf **fdf)
{
	int	tmp_x;
	int	tmp_y;
	int	tmp_z;

	tmp_x = ((*fdf)->a).x * cos((*fdf)->angle_y) + ((*fdf)->a).z * sin((*fdf)->angle_y);
	tmp_y = ((*fdf)->a).y;
	tmp_z = -((*fdf)->a).x * sin((*fdf)->angle_y) + ((*fdf)->a).z * cos((*fdf)->angle_y);
	((*fdf)->a).x = tmp_x;
	((*fdf)->a).y = tmp_y;
	((*fdf)->a).z = tmp_z;
	tmp_x = ((*fdf)->b).x * cos((*fdf)->angle_y) + ((*fdf)->b).z * sin((*fdf)->angle_y);
	tmp_y = ((*fdf)->b).y;
	tmp_z = -((*fdf)->b).x * sin((*fdf)->angle_y) + ((*fdf)->b).z * cos((*fdf)->angle_y);
	((*fdf)->b).x = tmp_x;
	((*fdf)->b).y = tmp_y;
	((*fdf)->b).z = tmp_z;
}

void rotate_z(t_fdf **fdf)
{
	int	tmp_x;
	int	tmp_y;
	int	tmp_z;

	tmp_x = ((*fdf)->a).x * cos((*fdf)->angle_z) - ((*fdf)->a).y * sin((*fdf)->angle_z);
	tmp_y = ((*fdf)->a).x * sin((*fdf)->angle_z) + ((*fdf)->a).y * cos((*fdf)->angle_z);
	tmp_z = ((*fdf)->a).z;
	((*fdf)->a).x = tmp_x;
	((*fdf)->a).y = tmp_y;
	((*fdf)->a).z = tmp_z;
	tmp_x = ((*fdf)->b).x * cos((*fdf)->angle_z) - ((*fdf)->b).y * sin((*fdf)->angle_z);
	tmp_y = ((*fdf)->b).x * sin((*fdf)->angle_z) + ((*fdf)->b).y * cos((*fdf)->angle_z);
	tmp_z = ((*fdf)->b).z;
	((*fdf)->b).x = tmp_x;
	((*fdf)->b).y = tmp_y;
	((*fdf)->b).z = tmp_z;
}

void init_fdf(t_fdf **fdf)
{
	int i;

	i = -1;
	(*fdf)->palette_ori[0] = 0xffffff;
	(*fdf)->palette_ori[1] = 0xff0000;
	while (++i < (*fdf)->palette_type)
		(*fdf)->palette_update[i] = (*fdf)->palette_ori[i];
	(*fdf)->projection = 'i';
	(*fdf)->angle = 0.6;
	(*fdf)->scale = 20;
	(*fdf)->scale_z = 1;
	(*fdf)->angle_x = 0;
	(*fdf)->angle_y = 0;
	(*fdf)->angle_z = 0;
	(*fdf)->move_x = WIDTH / 2;
	(*fdf)->move_y = 2 * HEIGHT / 5;
	if ((*fdf)->print_flat == 0)
		(*fdf)->palette_idx = 0;
	else if ((*fdf)->print_alt == 0)
		(*fdf)->palette_idx = 1;
	else
		(*fdf)->palette_idx = 2;
	(*fdf)->palette_sign = 1;
}

void plotLineChoice(t_fdf **fdf, int diff_x, int diff_y)
{
	if (diff_y < diff_x)
	{
		if (((*fdf)->a).x > ((*fdf)->b).x)
			plotLineLow(fdf, ((*fdf)->b), (*fdf)->a);
		else
			plotLineLow(fdf, ((*fdf)->a), ((*fdf)->b));
	}
	else
	{
		if (((*fdf)->a).y > ((*fdf)->b).y)
			plotLineHigh(fdf, ((*fdf)->b), ((*fdf)->a));
		else
			plotLineHigh(fdf, ((*fdf)->a), ((*fdf)->b));
	}
}

void plotLine(t_fdf **fdf)
{
	int diff_y;
	int diff_x;

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
	diff_y = ABS(diff_y);
	diff_x = ABS(diff_x);
	plotLineChoice(fdf, diff_x, diff_y);
}

void	print_string(int y, char *str, t_fdf *fdf, int input)
{
	char *full_str;
	char *input_str;

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

void print_color(t_fdf *fdf, int *i)
{
	int j;

	j = -1;
	print_string(++(*i), "Target of Color (0-9): ", fdf, fdf->palette_idx + 1);
	print_string(++(*i), "Change of Color (\\): ", fdf, fdf->palette_sign);
	while (++j < fdf->palette_type)
	{
		if (!((j == 0 && fdf->print_flat == 1) || (j == 1 && fdf->print_alt == 1)))
		{
			print_string(++(*i), "Details of Color ", fdf, j + 1);
			print_string(++(*i), "Transparency: ", fdf, (fdf->palette_update[j] >> 24) & 0xFF);
			print_string(++(*i), "R-color: ", fdf, (fdf->palette_update[j] >> 16) & 0xFF);
			print_string(++(*i), "G-color: ", fdf, (fdf->palette_update[j] >> 8) & 0xFF);
			print_string(++(*i), "B-color: ", fdf, fdf->palette_update[j] & 0xFF);
		}
	}
}

void	menu(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00, "Arrow key to move");
	print_string(++i, "Position X: ", fdf, fdf->move_x);
	print_string(++i, "Position Y: ", fdf, fdf->move_y);
	print_string(++i, "A/D to rotate x: ", fdf, (int)(fdf->angle_x * 10));
	print_string(++i, "W/S to rotate y: ", fdf, (int)(fdf->angle_y * 10));
	print_string(++i, "Q/E to rotate z: ", fdf, (int)(fdf->angle_z * 10));
	print_string(++i, "Z/X to change angle: ", fdf, (int)(fdf->angle * 10));
	print_string(++i, "+/- to scale up/down: ", fdf, fdf->scale - 20);
	print_string(++i, "[/] to scale alt: ", fdf, fdf->scale_z);
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00, "I: isometric projection");
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00, "C: cabinet projection");
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00, "O: oblique projection");
	print_string(++i, "Current projection: ", fdf, fdf->projection);
	print_color(fdf, &i);
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00, "SPACE Key to Reset");
	mlx_string_put(fdf->mlx, fdf->win, 5, 5 + (++i * 15), 0x00ff00, "ESC Key to Exit");
}

void update_color(int trgb, char c, t_fdf **fdf)
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
	(*fdf)->palette_update[(*fdf)->palette_idx] = (t << 24 | r << 16 | g << 8 | b);
}

void invert_color(int trgb, t_fdf **fdf)
{
	int neg;
	
	neg = (0xFFFFFF - trgb) | 0x00000000;
	(*fdf)->palette_update[(*fdf)->palette_idx] = neg;
}

void drawXY(t_fdf *fdf)
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
	fdf->img.addr = mlx_get_data_addr(fdf->img.mlx_img, &(fdf->img.bpp), &(fdf->img.line_len), &(fdf->img.endian));
	mlx_clear_window(fdf->mlx, fdf->win);
	drawXY(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.mlx_img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.mlx_img);
	menu(fdf);
	return (0);
}

void handle_numsnexit(int key, t_fdf **fdf)
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
	if (key == ESC_KEY)
	{
		mlx_destroy_window((*fdf)->mlx, (*fdf)->win);
		exit(EXIT_SUCCESS);
	}
}

void handle_orientation(int key, t_fdf **fdf)
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

void handle_colornmove(int key, t_fdf **fdf)
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
	handle_numsnexit(key, fdf);
	handle_orientation(key, fdf);
	handle_colornmove(key, fdf);
	mlx_clear_window((*fdf)->mlx, (*fdf)->win);
	draw(*fdf);
	return (0);
}

int	check_color(t_fdf **fdf, int *idx, int trgb)
{
	int	i;

	i = 1;
	if (*idx == 2)
		(*fdf)->palette_ori[*idx] = trgb;
	else
	{
		while (++i < *idx)
		{
			if ((*fdf)->palette_ori[i] == trgb)
				return (i);
		}
		(*fdf)->palette_ori[*idx] = trgb;
	}
	(*fdf)->palette_type = *idx + 1;
	return((*idx)++);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;
	int fd;

	if (ac != 2)
	{
		perror("Usage: ./fdf test_map");
		exit(EXIT_FAILURE);
	}
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
	{
		perror("Malloc fdf failed");
		exit(EXIT_FAILURE);
	}
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("File cannot be open");
		exit(EXIT_FAILURE);
	}
	char *str = get_next_line(fd);
	t_gnl_list	*input = NULL;
	t_gnl_list *node;
	char	**splitstr;
	int		i;
	fdf->width = 0;
	while (str)
	{
		i = -1;
		node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
		node->str = ft_strdup(str);
		node->next = NULL;
		splitstr = ft_split(node->str, ' ');
		while (splitstr[++i])
			free(splitstr[i]);
		free(splitstr);
		if (!fdf->width)
			fdf->width = i;
		else
		{
			if (fdf->width != i)
			{
				perror("Width not tallied");
				exit(EXIT_FAILURE);
			}
		}
		ft_lstadd_back_gnl(&input, node);
		free(str);
		str = get_next_line(fd);
	}
	fdf->height = ft_lstsize_gnl(input);
	fdf->matrix = (t_point **) malloc(sizeof(t_point *) * fdf->height);
	i = -1;
	fdf->print_flat = 1;
	fdf->print_alt = 1;
	int j;
	int	idx = 2;
	fdf->palette_type = 2;
	node = input;
	while (++i < fdf->height)
	{
		j = -1;
		fdf->matrix[i] = (t_point *) malloc(sizeof(t_point) * fdf->width);
		splitstr = ft_split(node->str, ' ');
		while (++j < fdf->width)
		{
			fdf->matrix[i][j].x = j;
			fdf->matrix[i][j].y = i;
			fdf->matrix[i][j].z = ft_atoi(splitstr[j]);
			char	*color = ft_strchr(splitstr[j], ',');
			if (color)
				fdf->matrix[i][j].color = check_color(&fdf, &idx, ft_atoh(&color[3]));
			else
			{
				if (fdf->matrix[i][j].z == 0)
				{
					fdf->print_flat = 0;
					fdf->matrix[i][j].color = 0;
				}
				else
				{
					fdf->print_alt = 0;
					fdf->matrix[i][j].color = 1;
				}
			}
			free(splitstr[j]);
		}
		free(splitstr);
		node = node->next;
	}
	init_fdf(&fdf);
	draw(fdf);
	mlx_key_hook(fdf->win, handle_keys, &fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
