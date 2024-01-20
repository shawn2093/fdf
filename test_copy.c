// #include <mlx.h>
#include "mlx/minilibx_macos/mlx.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include <time.h>
#include <math.h>
#include "fdf.h"

#define WIDTH 2000
#define HEIGHT 1400

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

// first.x < second.x
void plotLineLow(t_fdf **fdf, t_point *first, t_point *second)
{
	t_bres	a;

	a.dx = second->x - first->x;
	a.dy = second->y - first->y;
	a.yi = 1;
	if (a.dy < 0)
		a.yi = -1;
	a.dy = ABS(a.dy);
	a.D = (2 * a.dy) - a.dx;
	a.y = first->y;
	a.x = first->x;
	if (second->z)
		first->color = second->color;
	while (a.x <= second->x)
	{
		mlx_pixel_put((*fdf)->mlx, (*fdf)->win, a.x, a.y, first->color);
		if (a.D > 0)
		{
			a.y = a.y + a.yi;
			a.D = a.D + 2 * (a.dy - a.dx);
		}
		else
			a.D = a.D + 2 * a.dy;
		a.x++;
	}
}

//first.y < second.y
void plotLineHigh(t_fdf **fdf, t_point *first, t_point *second)
{
	t_bres	a;

	a.dx = second->x - first->x;
	a.dy = second->y - first->y;
	a.xi = 1;
	if (a.dx < 0)
		a.xi = -1;
	a.dx = ABS(a.dx);
	a.D = (2 * a.dx) - a.dy;
	a.y = first->y;
	a.x = first->x;
	if (second->z)
		first->color = second->color;
	while (a.y <= second->y)
	{
		mlx_pixel_put((*fdf)->mlx, (*fdf)->win, a.x, a.y, first->color);
		if (a.D > 0)
		{
			a.x = a.x + a.xi;
			a.D = a.D + 2 * (a.dx - a.dy);
		}
		else
			a.D = a.D + 2 * a.dx;
		a.y++;
	}
}

void plotLine(t_fdf **fdf)
{
	((*fdf)->a)->x = ((*fdf)->a)->x * (*fdf)->scale;
	((*fdf)->a)->y = ((*fdf)->a)->y * (*fdf)->scale;
	((*fdf)->b)->x = ((*fdf)->b)->x * (*fdf)->scale;
	((*fdf)->b)->y = ((*fdf)->b)->y * (*fdf)->scale;
	((*fdf)->a)->z = ((*fdf)->a)->z;
	((*fdf)->b)->z = ((*fdf)->b)->z;
	((*fdf)->a)->x = (((*fdf)->a)->x - ((*fdf)->a)->y) * cos(0.8) + 50;
	((*fdf)->a)->y = (((*fdf)->a)->x + ((*fdf)->a)->y) * sin(0.8) - ((*fdf)->a)->z + 50;
	((*fdf)->b)->x = (((*fdf)->b)->x - ((*fdf)->b)->y) * cos(0.8) + 50;
	((*fdf)->b)->y = (((*fdf)->b)->x + ((*fdf)->b)->y) * sin(0.8) - ((*fdf)->b)->z + 50;
	((*fdf)->a)->x = ((*fdf)->a)->x + 500 + (*fdf)->move_x;
	((*fdf)->a)->y = ((*fdf)->a)->y + 300 + (*fdf)->move_y;
	((*fdf)->b)->x = ((*fdf)->b)->x + 500 + (*fdf)->move_x;
	((*fdf)->b)->y = ((*fdf)->b)->y + 300 + (*fdf)->move_y;
	int diff_y = ((*fdf)->b)->y - ((*fdf)->a)->y;
	int diff_x = ((*fdf)->b)->x - ((*fdf)->a)->x;
	diff_y = ABS(diff_y);
	diff_x = ABS(diff_x);
	if (diff_y < diff_x)
	{
		if (((*fdf)->a)->x > ((*fdf)->b)->x)
			plotLineLow(fdf, ((*fdf)->b), (*fdf)->a);
		else
			plotLineLow(fdf, ((*fdf)->a), ((*fdf)->b));
	}
	else
	{
		if (((*fdf)->a)->y > ((*fdf)->b)->y)
			plotLineHigh(fdf, ((*fdf)->b), ((*fdf)->a));
		else
			plotLineHigh(fdf, ((*fdf)->a), ((*fdf)->b));
	}
}

void	draw(t_fdf *fdf)
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
				fdf->a->x = j;
				fdf->a->y = i;
				fdf->a->z = fdf->matrix[i][j];
				fdf->b->x = j;
				fdf->b->y = i + 1;
				fdf->b->z = fdf->matrix[i + 1][j];
				plotLine(&fdf);
			}
			if (j + 1 != fdf->width)
			{
				fdf->a->x = j;
				fdf->a->y = i;
				fdf->a->z = fdf->matrix[i][j];
				fdf->b->x = j + 1;
				fdf->b->y = i;
				fdf->b->z = fdf->matrix[i][j + 1];
				plotLine(&fdf);
			}
		}
	}
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
	fdf->matrix = (int **) malloc(sizeof(int *) * fdf->height);
	i = -1;
	int j;
	node = input;
	printf("wait\n");
	while (++i < fdf->height)
	{
		j = -1;
		fdf->matrix[i] = (int *) malloc(sizeof(int) * fdf->width);
		splitstr = ft_split(node->str, ' ');
		while (++j < fdf->width)
		{
			fdf->matrix[i][j] = ft_atoi(splitstr[j]);
			// char	*color = ft_strchr(splitstr[j], ',');
			// if (color)
			// 	fdf->matrix[i][j].color = ft_atoh(&color[3]);
			// else
			// {
			// 	if (fdf->matrix[i][j].z == 0)
			// 		fdf->matrix[i][j].color = 0xffffff;
			// 	else
			// 		fdf->matrix[i][j].color = 0xff0000;
			// }
			free(splitstr[j]);
		}
		free(splitstr);
		node = node->next;
	}
	fdf->scale = 50;
	draw(fdf);
	mlx_key_hook(fdf->win, handle_keys, &fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
