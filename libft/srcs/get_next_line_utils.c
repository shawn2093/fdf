/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:00:08 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:32:56 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl_list	*ft_lstlast_gnl(t_gnl_list *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		else
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_gnl(t_gnl_list **lst, t_gnl_list *new)
{
	t_gnl_list	*tmp;

	if (lst && new)
	{
		if (*lst)
		{
			tmp = ft_lstlast_gnl(*lst);
			tmp->next = new;
		}
		else
			*lst = new;
	}
}

int	ft_lstsize_gnl(t_gnl_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	make_new(t_gnl_list **bufstr, char *str)
{
	t_gnl_list	*new;
	t_gnl_list	*tmp;

	new = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!new)
		return ;
	new->str = str;
	new->next = NULL;
	while (*bufstr)
	{
		tmp = (*bufstr)->next;
		free((*bufstr)->str);
		free(*bufstr);
		*bufstr = tmp;
	}
	if (*str)
		*bufstr = new;
	else
	{
		free(str);
		free(new);
	}
}

void	clean_list(t_gnl_list **bufstr)
{
	int			i;
	int			k;
	t_gnl_list	*tmp;
	char		*str;

	if (!bufstr || !*bufstr)
		return ;
	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return ;
	tmp = ft_lstlast_gnl(*bufstr);
	i = -1;
	k = 0;
	while (tmp->str[++i])
	{
		if (tmp->str[i] == '\n')
			break ;
	}
	while (tmp->str[i++])
		str[k++] = tmp->str[i];
	str[k] = 0;
	make_new(bufstr, str);
}
