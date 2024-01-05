#include <mlx.h>
#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include <time.h>
#include <math.h>
#include "fdf.h"

#define WIDTH 1000
#define HEIGHT 700

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
	if (second.z)
		first.color = second.color;
	while (++a.x <= second.x)
	{
		img_pix_put(&((*fdf)->img), a.x, a.y, (unsigned int) first.color);
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
	if (second.z)
		first.color = second.color;
	while (++a.y <= second.y)
	{
		img_pix_put(&((*fdf)->img), a.x, a.y, (unsigned int) first.color);
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
	((*fdf)->a).x = (((*fdf)->a).x - ((*fdf)->a).y) * cos(0.8);
	((*fdf)->a).y = (((*fdf)->a).x + ((*fdf)->a).y) * sin(0.8) - ((*fdf)->a).z;
	((*fdf)->b).x = (((*fdf)->b).x - ((*fdf)->b).y) * cos(0.8);
	((*fdf)->b).y = (((*fdf)->b).x + ((*fdf)->b).y) * sin(0.8) - ((*fdf)->b).z;
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

void plotLine(t_fdf **fdf)
{
	int diff_y;
	int diff_x;

	zoom(fdf);
	rotate_x(fdf);
	rotate_y(fdf);
	rotate_z(fdf);
	isometric(fdf);
	move(fdf);
	diff_y = ((*fdf)->b).y - ((*fdf)->a).y;
	diff_x = ((*fdf)->b).x - ((*fdf)->a).x;
	diff_y = ABS(diff_y);
	diff_x = ABS(diff_x);
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

int	draw(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->img.mlx_img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.mlx_img, &(fdf->img.bpp), &(fdf->img.line_len), &(fdf->img.endian));
	mlx_clear_window(fdf->mlx, fdf->win);
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
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.mlx_img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.mlx_img);
	return (0);
}

int	handle_keys(int key, t_fdf **fdf)
{
	printf("%d\n", key);
	if (key == LEFT_KEY)
		(*fdf)->move_x -= 10;
	if (key == RIGHT_KEY)
		(*fdf)->move_x += 10;
	if (key == UP_KEY)
		(*fdf)->move_y -= 10;
	if (key == DOWN_KEY)
		(*fdf)->move_y += 10;
	if (key == PLUS_KEY)
		(*fdf)->scale += 1;
	if (key == MINUS_KEY && (*fdf)->scale > 5)
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
	if (key == ESC_KEY)
	{
		mlx_destroy_window((*fdf)->mlx, (*fdf)->win);
		exit(EXIT_SUCCESS);
	}
	mlx_clear_window((*fdf)->mlx, (*fdf)->win);
	draw(*fdf);
	return (0);
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
	fdf->win = mlx_new_window(fdf->mlx, 
				WIDTH,
				HEIGHT,
				"Pollock");
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
	int j;
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
				fdf->matrix[i][j].color = ft_atoh(&color[3]);
			else
			{
				if (fdf->matrix[i][j].z == 0)
					fdf->matrix[i][j].color = 0xffffff;
				else
					fdf->matrix[i][j].color = 0xff0000;
			}
			free(splitstr[j]);
		}
		free(splitstr);
		node = node->next;
	}
	fdf->scale = 20;
	fdf->scale_z = 1;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
	fdf->move_x = WIDTH / 2;
	fdf->move_y = 2 * HEIGHT / 5;
	draw(fdf);
	mlx_key_hook(fdf->win, handle_keys, &fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
