#include <mlx.h>
#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include <time.h>
#include <math.h>
#include "fdf.h"

#define WIDTH 2000
#define HEIGHT 1400

void drawline(void *win, void *mlx, int x1, int x2, int y1, int y2, t_point **matrix, int height, int width)
{
	// scale, isometric, shift
	(void) width;
	(void) height;
	t_point	a = matrix[x1][y1];
	t_point	b = matrix[x2][y2];
	a.x = a.x * 50;
	a.y = a.y * 50;
	b.x = b.x * 50;
	b.y = b.y * 50;
	a.x = (a.x - a.y) * cos(0.8) + 50;
	a.y = (a.x + a.y) * sin(0.8) - a.z + 50;
	b.x = (b.x - b.y) * cos(0.8) + 50;
	b.y = (b.x + b.y) * sin(0.8) - b.z + 50;
	// int a1 = (x11 - y11) * cos(0.8) + 50;
	// int b1 = ((x11 + y11) * sin(0.8) - matrix[y1][x1]) + 50;
	// int a2 = (x22 - y22) * cos(0.8) + 50;
	// int b2 = ((x22 + y22) * sin(0.8) - matrix[y2][x2]) + 50;

	// double a1 = ((x1 - y1) * cos(0.8)) * 50 + 100;
	// double b1 = ((x1 + y1)) * sin(0.8) - matrix[x1][y1];
	// double a2 = (x2 - y2) * cos(0.8);
	// double b2 = ((x2 + y2)) * sin(0.8) - matrix[x2][y2];
	a.x = a.x + 500;
	a.y = a.y + 300;
	b.x = b.x + 500;
	b.y = b.y + 300;
	// (void) matrix;
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
	int dx = x_max - x;
	int dy = y_max - y;
	int p = 2 * dx - dy;
	// while (x <= b.x)
	while (x <= x_max)
	{
		mlx_pixel_put(mlx, win, x, y, color);
		if (x <= x_max)
			x++;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p = p + 2 * dy - 2 * dx;
			// if (y > y_max)
			// {
			// 	y = y - 1;
			// }
			if (y < y_max)
			{
				y++;
			}
			// else if (y > y_max)
			// {
			// 	printf("minus\n");
			// 	y--;
			// }
		}
	}
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
	// for (int y = HEIGHT * 0.1; y < HEIGHT * 0.9; ++y)
	// {
	// 	for (int x = WIDTH * 0.1; x < WIDTH * 0.9; ++x)
	// 	{
	// 		mlx_pixel_put(mlx,
	// 			win, 
	// 			x, 
	// 			y,
	// 			rand() % 0xffffff);
	// 	}
	// }

	// int	x1 = 829;
	// int	x2 = 259;
	// int	y1 = 392;
	// int	y2 = 601;

	// for (int y = y1; y < y2; ++y)
	// {
	// 	float x = (y - y1) * (x2 - x1) / (y2 - y1) + x1;
	// 	mlx_pixel_put(mlx,
	// 			win, 
	// 			x, 
	// 			y,
	// 			0xffffff);
	// }

	// mlx_string_put(mlx,
	// 		win,
	// 		WIDTH * 0.7,
	// 		HEIGHT * 0.95,
	// 		0xff,
	// 		"POLLOCK");
	// mlx_loop(mlx);
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
				drawline(win, mlx, i, i + 1, j, j, matrix, height, width);
			if (j + 1 != width)
				drawline(win, mlx, i, i, j, j + 1, matrix, height, width);
		}
	}
	mlx_loop(mlx);
	return (0);
}