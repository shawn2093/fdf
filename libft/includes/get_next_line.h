/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:00:21 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:35:56 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl_list
{
	char				*str;
	struct s_gnl_list	*next;
}					t_gnl_list;

t_gnl_list	*ft_lstlast_gnl(t_gnl_list *lst);
void		ft_lstadd_back_gnl(t_gnl_list **lst, t_gnl_list *new);
int			ft_lstsize_gnl(t_gnl_list *lst);
void		make_new(t_gnl_list **bufstr, char *str);
void		clean_list(t_gnl_list **bufstr);
char		*fill_letters(t_gnl_list *bufstr, int len);
char		*get_line(t_gnl_list *bufstr);
int			found_nl(t_gnl_list **bufstr);
void		create_list(int fd, t_gnl_list **bufstr);
char		*get_next_line(int fd);

#endif