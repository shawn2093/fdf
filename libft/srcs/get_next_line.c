/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:00:38 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:32:41 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_letters(t_gnl_list *bufstr, int len)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * len + 2);
	if (!str)
		return (NULL);
	len = 0;
	while (bufstr)
	{
		i = -1;
		while (bufstr->str[++i])
		{
			str[len] = bufstr->str[i];
			len++;
			if (bufstr->str[i] == '\n')
				break ;
		}
		bufstr = bufstr->next;
	}
	str[len] = '\0';
	return (str);
}

char	*get_line(t_gnl_list *bufstr)
{
	int			count;
	t_gnl_list	*tmp;
	int			i;
	int			len;

	count = ft_lstsize_gnl(bufstr);
	tmp = ft_lstlast_gnl(bufstr);
	i = -1;
	while (tmp->str[++i])
	{
		if (tmp->str[i] == '\n')
			break ;
	}
	len = BUFFER_SIZE * (count - 1) + i;
	return (fill_letters(bufstr, len));
}

int	found_nl(t_gnl_list **bufstr)
{
	t_gnl_list	*tmp;
	int			i;

	tmp = *bufstr;
	while (tmp)
	{
		i = -1;
		while (tmp->str[++i])
		{
			if (tmp->str[i] == '\n')
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	create_list(int fd, t_gnl_list **bufstr)
{
	char		*str;
	size_t		buf;
	t_gnl_list	*tmp;

	while (!found_nl(bufstr))
	{
		str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!str)
			return ;
		buf = read(fd, str, BUFFER_SIZE);
		if (!buf)
		{
			free(str);
			return ;
		}
		str[buf] = 0;
		tmp = (t_gnl_list *)malloc(sizeof(t_gnl_list));
		tmp->str = str;
		tmp->next = 0;
		ft_lstadd_back_gnl(bufstr, tmp);
	}
}

char	*get_next_line(int fd)
{
	char				*str;
	static t_gnl_list	*bufstr[FOPEN_MAX];

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0 || read(fd, &str, 0) < 0)
		return (NULL);
	create_list(fd, &bufstr[fd]);
	if (bufstr[fd] == NULL)
		return (NULL);
	str = get_line(bufstr[fd]);
	clean_list(&bufstr[fd]);
	return (str);
}
