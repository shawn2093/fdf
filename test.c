#include <mlx.h>
#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include <time.h>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 700

void drawline(void *win, void *mlx, int x1, int x2, int y1, int y2, int **matrix)
{
	// double a1 = ((x1 - y1) * cos(0.8)) * 50 + 100;
	// double b1 = (((x1 + y1)) * sin(0.8) - matrix[x1][y1]) * 50 + 100;
	// double a2 = (x2 - y2) * cos(0.8) * 50 + 100;
	// double b2 = (((x2 + y2)) * sin(0.8) - matrix[x2][y2]) * 50 + 100;
	// double a1 = ((x1 - y1) * cos(0.8)) * 50 + 100;
	// double b1 = ((x1 + y1)) * sin(0.8) - matrix[x1][y1];
	// double a2 = (x2 - y2) * cos(0.8);
	// double b2 = ((x2 + y2)) * sin(0.8) - matrix[x2][y2];
	int a1 = x1 * 50 + 100;
	int b1 = y1 * 50 + 100;
	int a2 = x2 * 50 + 100;
	int b2 = y2 * 50 + 100;
	(void) matrix;
	for (int y = b1; y < b2; ++y)
	{
		if (y2 == y1)
		{
			for (int x = a1; x < a2; ++x)
				mlx_pixel_put(mlx, win, x, y, 0xffffff);
		}
		else
		{
			float	x;
			x = (y - b1) * (a2 - a1) / (b2 - b1) + a1;
			mlx_pixel_put(mlx, win, x, y, 0xffffff);
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
	int	**matrix;
	matrix = (int **) malloc(sizeof(int *) * height);
	i = -1;
	int j;
	node = input;
	while (++i < height)
	{
		j = -1;
		matrix[i] = (int *) malloc(sizeof(int) * width);
		splitstr = ft_split(node->str, ' ');
		while (++j < width)
		{
			matrix[i][j] = ft_atoi(splitstr[j]);
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
				drawline(win, mlx, i, i + 1, j, j, matrix);
			if (j + 1 != width)
				drawline(win, mlx, i, i, j, j + 1, matrix);
		}
	}
	// void drawline(void *win, void *mlx, int x1, int x2, int y1, int y2, int **matrix)
	mlx_loop(mlx);
	return (0);
}