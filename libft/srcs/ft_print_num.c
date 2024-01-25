/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:01:08 by long              #+#    #+#             */
/*   Updated: 2023/11/28 16:39:02 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(void *i, t_flags flag)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_htoa((unsigned long long)i, flag.type);
	flag.width -= ((int)ft_strlen(str) + 2);
	if (!flag.left)
	{
		len += ft_putpad_len(' ', flag.width);
		if ((unsigned long long)i == 0)
			len += ft_putstr_len(PTRNULL);
		else
			len += (ft_putstr_len("0x") + ft_putstr_len(str));
	}
	else
	{
		if ((unsigned long long)i == 0)
			len += ft_putstr_len(PTRNULL);
		else
			len += (ft_putstr_len("0x") + ft_putstr_len(str));
		len += ft_putpad_len(' ', flag.width);
	}
	free(str);
	return (len);
}

static int	ft_printuxid_helper(char *str, char *icon, t_flags flag)
{
	int	len;

	len = 0;
	if (!flag.dot || flag.precision < (int)ft_strlen(str))
		flag.precision = (int)ft_strlen(str);
	flag.width -= (flag.precision + (int)ft_strlen(icon));
	flag.precision -= (int)ft_strlen(str);
	if (!flag.left)
	{
		if (flag.zero && !flag.dot)
			len += (ft_putstr_len(icon) + ft_putpad_len('0', flag.width));
		else
			len += (ft_putpad_len(' ', flag.width) + ft_putstr_len(icon));
	}
	if (flag.left)
		len += ft_putstr_len(icon);
	if (flag.dot)
		len += ft_putpad_len('0', flag.precision);
	if (!flag.left)
		return (len + ft_putstr_len(str));
	return (len + ft_putstr_len(str) + ft_putpad_len(' ', flag.width));
}

int	ft_print_ux(unsigned int i, t_flags flag)
{
	int		len;
	char	*str;
	char	*hash;

	hash = "";
	if (i == 0 && flag.precision == 0)
		str = ft_strdup("");
	else
		str = ft_htoa((unsigned long long)i, flag.type);
	if (flag.hash && i != 0 && (flag.type == 'X' || flag.type == 'x'))
	{
		if (flag.type == 'X')
			hash = "0X";
		else
			hash = "0x";
	}
	len = ft_printuxid_helper(str, hash, flag);
	free(str);
	return (len);
}

int	ft_print_int(int i, t_flags flag)
{
	int		len;
	char	*ptr;
	char	*str;
	char	*symbol;

	symbol = "";
	if (i == 0 && flag.precision == 0)
		ptr = ft_strdup("");
	else
		ptr = ft_itoa(i);
	str = ptr;
	if (flag.space)
		symbol = " ";
	if (flag.plus)
		symbol = "+";
	if (i < 0)
	{
		str++;
		symbol = "-";
	}
	len = ft_printuxid_helper(str, symbol, flag);
	free(ptr);
	return (len);
}
