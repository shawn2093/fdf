/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:58:49 by long              #+#    #+#             */
/*   Updated: 2024/01/27 17:14:13 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_fdf(t_fdf **fdf)
{
	int	i;

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

void	check_width(t_fdf **fdf, t_gnl_list *node)
{
	char	**splitstr;
	int		i;

	i = -1;
	splitstr = ft_split(node->str, ' ');
	while (splitstr[++i])
		free(splitstr[i]);
	free(splitstr);
	if (!(*fdf)->width)
		(*fdf)->width = i;
	else
	{
		if ((*fdf)->width != i)
		{
			perror("Width not tallied");
			exit(EXIT_FAILURE);
		}
	}
}

void	read_map(int fd, t_gnl_list **input, t_fdf **fdf)
{
	char		*str;
	t_gnl_list	*node;

	str = get_next_line(fd);
	while (str)
	{
		node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
		if (!node)
		{
			perror("Malloc node failed.");
			exit(EXIT_FAILURE);
		}
		node->str = ft_strdup(str);
		node->next = NULL;
		check_width(fdf, node);
		ft_lstadd_back_gnl(input, node);
		free(str);
		str = get_next_line(fd);
	}
	(*fdf)->height = ft_lstsize_gnl(*input);
}

int	error_handle(int ac, char **av)
{
	int	fd;
	int	len;

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
	len = ft_strlen(av[1]);
	if (!(av[1][len - 1] == 'f' && av[1][len - 2] == 'd'
		&& av[1][len - 3] == 'f' && av[1][len - 4] == '.'))
	{
		perror("Incorrect file format");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	main(int ac, char **av)
{
	t_fdf		*fdf;
	int			fd;
	t_gnl_list	*input;

	fd = error_handle(ac, av);
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
	{
		perror("Malloc fdf failed");
		exit(EXIT_FAILURE);
	}
	input = NULL;
	fdf->width = 0;
	read_map(fd, &input, &fdf);
	do_matrix(&fdf, input);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	init_fdf(&fdf);
	draw(fdf);
	mlx_hook(fdf->win, 17, 0, mlx_close, &fdf);
	mlx_key_hook(fdf->win, handle_keys, &fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
