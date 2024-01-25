/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:06:36 by long              #+#    #+#             */
/*   Updated: 2023/11/28 16:38:59 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_len(char i)
{
	ft_putchar_fd(i, 1);
	return (1);
}

int	ft_putstr_len(char *i)
{
	int	len;

	len = -1;
	while (i[++len])
		ft_putchar_len(i[len]);
	return ((int)ft_strlen(i));
}

int	ft_putpad_len(char i, int len)
{
	int	index;

	index = 0;
	while (len > 0)
	{
		index += ft_putchar_len(i);
		len--;
	}
	return (index);
}

int	ft_print_char(char i, t_flags flag)
{
	int	len;

	len = 0;
	flag.width--;
	if (!flag.left)
	{
		len += ft_putpad_len(' ', flag.width);
		len += ft_putchar_len(i);
	}
	else
	{
		len += ft_putchar_len(i);
		len += ft_putpad_len(' ', flag.width);
	}
	return (len);
}

int	ft_print_str(char *i, t_flags flag)
{
	int		len;
	char	*str;

	len = 0;
	if (!i)
		i = "(null)";
	if (!flag.dot || flag.precision > (int)ft_strlen(i))
		flag.precision = (int)ft_strlen(i);
	str = ft_substr((char const *)i, 0, (size_t)flag.precision);
	flag.width -= flag.precision;
	if (!flag.left)
	{
		len += ft_putpad_len(' ', flag.width);
		len += ft_putstr_len(str);
	}
	else
	{
		len += ft_putstr_len(str);
		len += ft_putpad_len(' ', flag.width);
	}
	free(str);
	return (len);
}
