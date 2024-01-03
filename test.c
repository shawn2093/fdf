#include <mlx.h>
#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include <time.h>
#include <math.h>
#include "fdf.h"

#define WIDTH 2000
#define HEIGHT 1400

void drawline(void *win, void *mlx, t_point first, t_point second)
{
	// scale, isometric, shift
	t_point	a = first;
	t_point	b = second;
	a.x = a.x * 50;
	a.y = a.y * 50;
	b.x = b.x * 50;
	b.y = b.y * 50;
	a.x = (a.x - a.y) * cos(0.8) + 50;
	a.y = (a.x + a.y) * sin(0.8) - a.z + 50;
	b.x = (b.x - b.y) * cos(0.8) + 50;
	b.y = (b.x + b.y) * sin(0.8) - b.z + 50;
	a.x = a.x + 500;
	a.y = a.y + 300;
	b.x = b.x + 500;
	b.y = b.y + 300;
	int color = 0xffffff;
	if (a.z || b.z)
		color = 0xff0000;
	int x = MIN(a.x, b.x);
	int x_max = MAX(a.x, b.x);
	int y;
	int y_max;
	if (x == a.x)
	{
		y = a.y;
		y_max = b.y;
	}
	else
	{
		y = b.y;
		y_max = a.y;
	}

	int step_x = x_max - x;
	int step_y = y_max - y;
	int max = MAX(ABS(step_x), ABS(step_y));
	int i = 0;
	printf("x: %d y: %d\n", x, y);
	printf("step_x: %d step_y: %d\n", step_x, step_y);
	printf("x_max: %d y_max: %d\n", x_max, y_max);
	printf("MAX: %d\n", max);
	// while ((int)(x_max - x) || (int)(y_max - y))
	// {
	// 	i++;
	// 	mlx_pixel_put(mlx, win, x, y, color);
	// 	x = x + (step_x * i) / max;
	// 	y = y + (step_y * i) / max;
	// 	printf("x: %d y: %d\n", x, y);
	// 	if ((step_x * i) / max && (step_y * i) / max)
	// 		i = 0;
	// 	if (x < 0 || y < 0 || x > x_max)
	// 		break ;
	// }

	while ((int)(x_max - x) || (int)(y_max - y))
	{
		i++;
		mlx_pixel_put(mlx, win, x, y, color);
		if (x_max - x)
			x = x + (step_x * i) / max;
		if (y_max - y)
			y = y + (step_y * i) / max;
		if ((step_x * i) / max && (step_y * i) / max)
			i = 0;
		if (x < 0 || y < 0 || x - x_max != 0 || y - y_max != 0)
			break ;
	}

	// int dx = ABS(x_max - x);
	// int dy = -ABS(y_max - x);
	// int sx = 1;
	// int sy = 1;
	// if (x > x_max)
	// 	sx = -1;
	// if (y > y_max)
	// 	sy = -1;
	// // int p = 2 * dx - dy;
	// // int p = 2 * dy - dx;
	// // int i = 0;
	// int	error = dx + dy;
	// while (1)
	// {
	// 	mlx_pixel_put(mlx, win, x, y, color);
	// 	if (x == x_max && y == y_max)
	// 		break ;
	// 	int e2 = 2 * error;
	// 	if (e2 >= dy)
	// 	{
	// 		if (x == x_max)
	// 			break ;
	// 		error = error + dy;
	// 		x = x + sx;
	// 	}
	// 	if (e2 <= dx)
	// 	{
	// 		if (y == y_max)
	// 			break ;
	// 		error = error + dx;
	// 		y = y + sy;
	// 	}
	// }


	// while (x <= x_max)
	// {
	// 	mlx_pixel_put(mlx, win, x, y, color);
	// 	x++;
	// 	if (p < 0)
	// 	{
	// 		i++;
	// 		p = p + 2 * dy;
	// 		// if (y < y_max)
	// 		// {
	// 		// 	y++;
	// 		// }
	// 		if (y > y_max)
	// 		{
	// 			y = y + (dy * i / dx);
	// 			if ((dy * i) / dx != 0)
	// 				i = 0;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		p = p + 2 * dy - 2 * dx;
	// 		// if (y > y_max)
	// 		// {
	// 		// 	y = y - 1;
	// 		// }
	// 		if (y < y_max)
	// 		{
	// 			y++;
	// 		}
	// 		// if (y > y_max)
	// 		// {
	// 		// 	y--;
	// 		// }
	// 		// else if (y > y_max)
	// 		// {
	// 		// 	y--;
	// 		// }
	// 	}
	// }

}

int	main(int ac, char **av)
{
	void	*win;
	void	*mlx;

	// srand(time(NULL));
	mlx = mlx_init();
	win = mlx_new_window(mlx, 
				WIDTH,
				HEIGHT,
				"Pollock");
	
	int fd;
	
	if (ac != 2)
	{
		perror("Usage: ./fdf test_map");
		exit(EXIT_FAILURE);
	}
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
	int		width;
	int		i;
	width = 0;
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
		i--;
		if (!width)
			width = i;
		else
		{
			if (width != i)
			{
				perror("Width not tallied");
				exit(EXIT_FAILURE);
			}
		}
		ft_lstadd_back_gnl(&input, node);
		free(str);
		str = get_next_line(fd);
	}
	int height = ft_lstsize_gnl(input);
	t_point	**matrix;
	matrix = (t_point **) malloc(sizeof(t_point *) * height);
	i = -1;
	int j;
	node = input;
	while (++i < height)
	{
		j = -1;
		matrix[i] = (t_point *) malloc(sizeof(t_point) * width);
		splitstr = ft_split(node->str, ' ');
		while (++j < width)
		{
			matrix[i][j].x = j;
			matrix[i][j].y = i;
			matrix[i][j].z = ft_atoi(splitstr[j]);
			free(splitstr[j]);
		}
		free(splitstr);
		node = node->next;
	}
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (i + 1 != height)
				drawline(win, mlx, matrix[i][j], matrix[i + 1][j]);
				// drawline(win, mlx, matrix[j][i], matrix[j][i + 1]);
			if (j + 1 != width)
				drawline(win, mlx, matrix[i][j], matrix[i][j + 1]);
				// drawline(win, mlx, matrix[j][i], matrix[j + 1][i]);
		}
	}
	mlx_loop(mlx);
	return (0);
}

// void print_point(t_point first, t_point second)
// {
// 	// scale, isometric, shift
// 	t_point	a = first;
// 	t_point	b = second;
// 	a.x = a.x * 50;
// 	a.y = a.y * 50;
// 	b.x = b.x * 50;
// 	b.y = b.y * 50;
// 	a.x = (a.x - a.y) * cos(0.8) + 50;
// 	a.y = (a.x + a.y) * sin(0.8) - a.z + 50;
// 	b.x = (b.x - b.y) * cos(0.8) + 50;
// 	b.y = (b.x + b.y) * sin(0.8) - b.z + 50;
// 	// int a1 = (x11 - y11) * cos(0.8) + 50;
// 	// int b1 = ((x11 + y11) * sin(0.8) - matrix[y1][x1]) + 50;
// 	// int a2 = (x22 - y22) * cos(0.8) + 50;
// 	// int b2 = ((x22 + y22) * sin(0.8) - matrix[y2][x2]) + 50;
// 	a.x = a.x + 500;
// 	a.y = a.y + 300;
// 	b.x = b.x + 500;
// 	b.y = b.y + 300;
// 	int color = 0xffffff;
// 	if (a.z || b.z)
// 		color = 0xff0000;
// 	int x = MIN(a.x, b.x);
// 	int x_max = MAX(a.x, b.x);
// 	int y;
// 	int y_max;
// 	if (x == a.x)
// 	{
// 		y = a.y;
// 		y_max = b.y;
// 	}
// 	else
// 	{
// 		y = b.y;
// 		y_max = a.y;
// 	}
// 	int dx = x_max - x;
// 	int dy = y_max - y;
// 	// int p = 2 * dx - dy;
// 	int p = 2 * dy - dx;
// 	int i = 0;
// 	while (x <= x_max)
// 	{
// 		printf("x: %d y: %d\n", x, y);
// 		x++;
// 		if (p < 0)
// 		{
// 			i++;
// 			p = p + 2 * dy;
// 			// if (y < y_max)
// 			// {
// 			// 	y++;
// 			// }
// 			if (y > y_max)
// 			{
// 				y = y + (dy * i / dx);
// 				if ((dy * i) / dx != 0)
// 					i = 0;
// 			}
// 		}
// 		else
// 		{
// 			p = p + 2 * dy - 2 * dx;
// 			// if (y > y_max)
// 			// {
// 			// 	y = y - 1;
// 			// }
// 			if (y < y_max)
// 			{
// 				y++;
// 			}
// 			// if (y > y_max)
// 			// {
// 			// 	y--;
// 			// }
// 			// else if (y > y_max)
// 			// {
// 			// 	y--;
// 			// }
// 		}
// 	}
// }

// int	main(void)
// {
// 	t_point	a;
// 	t_point b;
// 	t_point c;
// 	t_point d;
// 	void	*win;
// 	void	*mlx;

// 	a.x = 0;
// 	a.y = 0;
// 	a.z = -6;
// 	b.x = 1;
// 	b.y = 0;
// 	b.z = -67;
// 	c.x = 0;
// 	c.y = 1;
// 	c.z = 27;
// 	d.x = 1;
// 	d.y = 1;
// 	d.z = -63;
// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 
// 				WIDTH,
// 				HEIGHT,
// 				"Pollock");
// 	drawline(win, mlx, a, b);
// 	drawline(win, mlx, a, c);
// 	drawline(win, mlx, b, d);
// 	drawline(win, mlx, c, d);
// 	// printf("a->b: \n");
// 	// print_point(a, b);
// 	// printf("b->d: \n");
// 	// print_point(b, d);
// 	mlx_loop(mlx);
// 	return (0);
// }