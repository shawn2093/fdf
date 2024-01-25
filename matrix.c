/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:59:06 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:02:33 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoh(const char *str)
{
	int	res;

	res = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	while ((*str >= '0' && *str <= '9')
		|| (*str >= 'a' && *str <= 'f')
		|| (*str >= 'A' && *str <= 'F'))
	{
		if (*str >= '0' && *str <= '9')
			res = res * 16 + *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			res = res * 16 + *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			res = res * 16 + *str - 'A' + 10;
		str++;
	}
	return (res);
}

void	check_flatnalt(t_fdf **fdf, int i, int j)
{
	if ((*fdf)->matrix[i][j].z == 0)
	{
		(*fdf)->print_flat = 0;
		(*fdf)->matrix[i][j].color = 0;
	}
	else
	{
		(*fdf)->print_alt = 0;
		(*fdf)->matrix[i][j].color = 1;
	}
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
	return ((*idx)++);
}

void	fill_matrix(t_fdf **fdf, int i, int *idx, t_gnl_list *input)
{
	char	**splitstr;
	int		j;
	char	*color;

	splitstr = ft_split(input->str, ' ');
	j = -1;
	while (++j < (*fdf)->width)
	{
		(*fdf)->matrix[i][j].x = j;
		(*fdf)->matrix[i][j].y = i;
		(*fdf)->matrix[i][j].z = ft_atoi(splitstr[j]);
		color = ft_strchr(splitstr[j], ',');
		if (color)
			(*fdf)->matrix[i][j].color = check_color(fdf, idx,
					ft_atoh(&color[3]));
		else
			check_flatnalt(fdf, i, j);
		free(splitstr[j]);
	}
	free(splitstr);
}

void	do_matrix(t_fdf **fdf, t_gnl_list *input)
{
	int	i;
	int	idx;

	i = -1;
	(*fdf)->print_flat = 1;
	(*fdf)->print_alt = 1;
	idx = 2;
	(*fdf)->palette_type = 2;
	(*fdf)->matrix = (t_point **)malloc(sizeof(t_point *) * (*fdf)->height);
	if (!(*fdf)->matrix)
	{
		perror("Malloc fdf->matrix failed.");
		exit(EXIT_FAILURE);
	}
	while (++i < (*fdf)->height)
	{
		(*fdf)->matrix[i] = (t_point *)malloc(sizeof(t_point) * (*fdf)->width);
		if (!(*fdf)->matrix[i])
		{
			perror("Malloc fdf->matrix[i] failed.");
			exit(EXIT_FAILURE);
		}
		fill_matrix(fdf, i, &idx, input);
		input = input->next;
	}
}
