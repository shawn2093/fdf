#include <mlx.h>
#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include <time.h>

#define WIDTH 1000
#define HEIGHT 700


int	main(int ac, char **av)
{
	// void	*win;
	// void	*mlx;

	// srand(time(NULL));
	// mlx = mlx_init();
	// win = mlx_new_window(mlx, 
	// 			WIDTH,
	// 			HEIGHT,
	// 			"Pollock");
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
	t_list	**input = NULL;
	t_list *node;
	while (str)
	{
		node = ft_lstnew(str);
		ft_printf("%s", node->content);
		ft_lstadd_back(input, node);
		free(str);
		free(node);
		str = get_next_line(fd);
	}
	char	**splitstr = ft_split((char *) (*input)->content, ' ');
	int height = ft_lstsize(*input);
	int	width = sizeof(splitstr[0]);
	ft_printf("height: %d width: %d", height, width);
	// node = *input;
	// ft_printf("done\n");
	// while (node)
	// {
	// 	ft_printf("%s\n", node->content);
	// 	node = node->next;
	// }
	return (0);
}