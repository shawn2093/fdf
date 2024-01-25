/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:47:28 by long              #+#    #+#             */
/*   Updated: 2024/01/26 02:35:14 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// # if defined (__linux__)
// #  define PTRNULL "(nil)"
// # elif defined (__APPLE__)
// #  define PTRNULL "0x0"
// # endif

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags
{
	int	type;
	int	left;
	int	space;
	int	plus;
	int	zero;
	int	hash;
	int	dot;
	int	width;
	int	precision;
}		t_flags;

int		ft_print_ptr(void *i, t_flags flag);
int		ft_print_ux(unsigned int i, t_flags flag);
int		ft_print_int(int i, t_flags flag);
t_flags	ft_flags_init(void);
char	*ft_htoa(unsigned long long n, int i);
int		ft_putchar_len(char i);
int		ft_putstr_len(char *i);
int		ft_putpad_len(char i, int len);
int		ft_print_char(char i, t_flags flag);
int		ft_print_str(char *i, t_flags flag);
int		ft_printf(const char *format, ...);

#endif