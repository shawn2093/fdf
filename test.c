#include <mlx.h>
#include "libft/includes/ft_printf.h"
#include "libft/includes/libft.h"
// #include "libft/includes/get_next_line.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

    ft_printf("lets try this out\n");
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}