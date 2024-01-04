// void drawline(void *win, void *mlx, t_point first, t_point second)
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

// 	float	step_x;
// 	float	step_y;
// 	float	max;
// 	float	x_float = (float) x;
// 	float 	y_float = (float) y;
// 	step_x = b.x - a.x;
// 	step_y = b.y - a.y;
// 	max = MAX(ABS(step_x), ABS(step_y));
// 	step_x /= max;
// 	step_y /= max;
// 	while ((int)(x_float - x_max) || (int)(y_float - y_max))
// 	{
// 		mlx_pixel_put(mlx, win, x_float, y_float, color);
// 		x_float = x_float + step_x;
// 		y_float = y_float + step_y;
// 		if (x_float > WIDTH || y_float > HEIGHT || x_float < 0 || y_float < 0)
// 			break ;
// 	}

// 	// int step_x = x_max - x;
// 	// int step_y = y_max - y;
// 	// int max = MAX(ABS(step_x), ABS(step_y));
// 	// int i = 0;
// 	// int j = 0;
// 	// printf("x: %d y: %d\n", x, y);
// 	// printf("step_x: %d step_y: %d\n", step_x, step_y);
// 	// printf("x_max: %d y_max: %d\n", x_max, y_max);
// 	// printf("MAX: %d\n", max);
// 	// while ((int)(x_max - x) || (int)(y_max - y))
// 	// {
// 	// 	i++;
// 	// 	mlx_pixel_put(mlx, win, x, y, color);
// 	// 	x = x + (step_x * i) / max;
// 	// 	y = y + (step_y * i) / max;
// 	// 	printf("x: %d y: %d\n", x, y);
// 	// 	if ((step_x * i) / max && (step_y * i) / max)
// 	// 		i = 0;
// 	// 	if (x < 0 || y < 0 || x > x_max)
// 	// 		break ;
// 	// }

// 	// while ((int)(x_max - x) || (int)(y_max - y))
// 	// {
// 	// 	i++;
// 	// 	j++;
// 	// 	mlx_pixel_put(mlx, win, x, y, color);
// 	// 	x = x + (step_x * i) / max;
// 	// 	y = y + (step_y * j) / max;
// 	// 	if ((step_x * i) / max)
// 	// 		i = 0;
// 	// 	if ((step_y * j) / max)
// 	// 		j = 0;
// 	// 	if (x < 0 || y < 0 || x > x_max || (y <= y_max && y + 1 > y_max) || (y >= y_max && y - 1 < y_max))
// 	// 		break ;
// 	// }

// 	// int dx = ABS(x_max - x);
// 	// int dy = -ABS(y_max - x);
// 	// int sx = 1;
// 	// int sy = 1;
// 	// if (x > x_max)
// 	// 	sx = -1;
// 	// if (y > y_max)
// 	// 	sy = -1;
// 	// // int p = 2 * dx - dy;
// 	// // int p = 2 * dy - dx;
// 	// // int i = 0;
// 	// int	error = dx + dy;
// 	// while (1)
// 	// {
// 	// 	mlx_pixel_put(mlx, win, x, y, color);
// 	// 	if (x == x_max && y == y_max)
// 	// 		break ;
// 	// 	int e2 = 2 * error;
// 	// 	if (e2 >= dy)
// 	// 	{
// 	// 		if (x == x_max)
// 	// 			break ;
// 	// 		error = error + dy;
// 	// 		x = x + sx;
// 	// 	}
// 	// 	if (e2 <= dx)
// 	// 	{
// 	// 		if (y == y_max)
// 	// 			break ;
// 	// 		error = error + dx;
// 	// 		y = y + sy;
// 	// 	}
// 	// }

// 	// int	i = 0;
// 	// int dx = x_max - x;
// 	// int dy = y_max - y;
// 	// int p = 2 *dy - dx;
// 	// while (x <= x_max)
// 	// {
// 	// 	mlx_pixel_put(mlx, win, x, y, color);
// 	// 	x++;
// 	// 	if (p < 0)
// 	// 	{
// 	// 		i++;
// 	// 		p = p + 2 * dy;
// 	// 		// if (y < y_max)
// 	// 		// {
// 	// 		// 	y++;
// 	// 		// }
// 	// 		if (y > y_max)
// 	// 		{
// 	// 			y = y + (dy * i / dx);
// 	// 			if ((dy * i) / dx != 0)
// 	// 				i = 0;
// 	// 		}
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		p = p + 2 * dy - 2 * dx;
// 	// 		// if (y > y_max)
// 	// 		// {
// 	// 		// 	y = y - 1;
// 	// 		// }
// 	// 		if (y < y_max)
// 	// 		{
// 	// 			y++;
// 	// 		}
// 	// 		// if (y > y_max)
// 	// 		// {
// 	// 		// 	y--;
// 	// 		// }
// 	// 		// else if (y > y_max)
// 	// 		// {
// 	// 		// 	y--;
// 	// 		// }
// 	// 	}
// 	// }
// }

// // first.x < second.x
// void plotLineLow(t_fdf **fdf, t_point first, t_point second)
// {
// 	int dx = second.x - first.x;
// 	int dy = second.y - first.y;
// 	int yi = 1;
// 	if (dy < 0)
// 	{
// 		yi = -1;
// 		dy = -dy;
// 	}
// 	int D = (2 * dy) - dx;
// 	int y = first.y;
// 	int x = first.x;
// 	if (second.z)
// 		first.color = second.color;
// 	while (x <= second.x)
// 	{
// 		mlx_pixel_put((*fdf)->mlx, (*fdf)->win, x, y, first.color);
// 		if (D > 0)
// 		{
// 			y = y + yi;
// 			D = D + 2 * (dy - dx);
// 		}
// 		else
// 			D = D + 2 * dy;
// 		x++;
// 	}
// }

// //first.y < second.y
// void plotLineHigh(t_fdf **fdf, t_point first, t_point second)
// {
// 	int	dx = second.x - first.x;
// 	int dy = second.y - first.y;
// 	int xi = 1;
// 	if (dx < 0)
// 	{
// 		xi = -1;
// 		dx = -dx;
// 	}
// 	int D = (2 * dx) - dy;
// 	int x = first.x;
// 	int y = first.y;
// 	if (second.z)
// 		first.color = second.color;
// 	while (y <= second.y)
// 	{
// 		mlx_pixel_put((*fdf)->mlx, (*fdf)->win, x, y, first.color);
// 		if (D > 0)
// 		{
// 			x = x + xi;
// 			D = D + 2 * (dx - dy);
// 		}
// 		else
// 			D = D + 2 * dx;
// 		y++;
// 	}
// }



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

// i = -1;
// while (++i < fdf->height)
// {
// 	j = -1;
// 	while (++j < fdf->width)
// 	{
// 		if (i + 1 != fdf->height)
// 		{
// 			fdf->a = matrix[i][j];
// 			fdf->b = matrix[i + 1][j];
// 			// plotLine(&fdf, matrix[i][j], matrix[i + 1][j]);
// 			// plotLine(&fdf, fdf->a, fdf->b);
// 			plotLine(&fdf);
// 		}
// 		if (j + 1 != fdf->width)
// 		{
// 			fdf->a = matrix[i][j];
// 			fdf->b = matrix[i][j + 1];
// 			// plotLine(&fdf, matrix[i][j], matrix[i][j + 1]);
// 			// plotLine(&fdf, fdf->a, fdf->b);
// 			plotLine(&fdf);
// 		}
// 	}
// }