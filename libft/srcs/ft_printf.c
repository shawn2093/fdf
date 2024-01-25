/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: long <long@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:46:37 by long              #+#    #+#             */
/*   Updated: 2023/11/28 16:40:36 by long             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_isflag(char i)
{
	char	*flags;
	int		index;

	flags = "-+ #0";
	index = -1;
	while (flags[++index])
	{
		if (i == flags[index])
			return (1);
	}
	return (0);
}

static int	ft_print_args(const char *format, int *i, t_flags flag,
		va_list args)
{
	int	len;

	len = 0;
	flag.type = format[*i];
	if (format[*i] == '%')
		len += ft_putchar_len('%');
	else if (format[*i] == 'c')
		len += ft_print_char(va_arg(args, int), flag);
	else if (format[*i] == 's')
		len += ft_print_str(va_arg(args, char *), flag);
	else if (format[*i] == 'p')
		len += ft_print_ptr(va_arg(args, void *), flag);
	else if (format[*i] == 'd' || format[*i] == 'i')
		len += ft_print_int(va_arg(args, int), flag);
	else if (format[*i] == 'X' || format[*i] == 'x' || format[*i] == 'u')
		len += ft_print_ux(va_arg(args, unsigned int), flag);
	return (len);
}

static t_flags	ft_check_wp(const char *format, int *i, t_flags flag)
{
	flag.width = ft_atoi(&format[*i]);
	while (ft_isdigit(format[*i]))
		(*i)++;
	if (format[*i] == '.')
	{
		flag.dot = 1;
		(*i)++;
		flag.precision = ft_atoi(&format[*i]);
		while (ft_isdigit(format[*i]))
			(*i)++;
	}
	return (flag);
}

static t_flags	ft_check_flags(const char *format, int *i, t_flags flag)
{
	while (ft_isflag(format[++(*i)]))
	{
		if (format[*i] == '-')
			flag.left = 1;
		if (format[*i] == '+')
			flag.plus = 1;
		if (format[*i] == ' ')
			flag.space = 1;
		if (format[*i] == '#')
			flag.hash = 1;
		if (format[*i] == '0')
			flag.zero = 1;
	}
	flag = ft_check_wp(format, i, flag);
	return (flag);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flag;
	int		i;
	int		len;

	if (!format || *format == '\0')
		return (0);
	i = -1;
	len = 0;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			flag = ft_flags_init();
			flag = ft_check_flags(format, &i, flag);
			len += ft_print_args(format, &i, flag, args);
		}
		else
			len += ft_putchar_len(format[i]);
	}
	va_end(args);
	return (len);
}

// int main(void)
// {
//     // "-+ #0" "cspdiuxX"

//     // printf("100%%\n");
//     // printf("100%5%\n");
//     // printf("100%5.3%\n");
//     // printf("100%5.7%\n");
//     // printf("100%05.3%\n");
//     // printf("100%-5%\n");
//     // printf("100%+5%\n");
//     // printf("100% 5%\n");
//     // printf("100%#5%\n");
//     // printf("100%05%\n");
//     // printf("--------------------\n");
//     // ft_printf("100%%\n");
//     // ft_printf("100%5%\n");
//     // ft_printf("100%5.3%\n");
//     // ft_printf("100%5.7%\n");
//     // ft_printf("100%05.3%\n");
//     // ft_printf("100%-5%\n");
//     // ft_printf("100%+5%\n");
//     // ft_printf("100% 5%\n");
//     // ft_printf("100%#5%\n");
//     // ft_printf("100%05%\n");

//     // printf("+++++++++++++++++++++++++++++\n");
//     // printf("%c\n", 'H');
//     // printf("%5c\n", 'H');
//     // printf("%-5c\n", 'H');
//     // printf("-----------------------------\n");
//     // ft_printf("%c\n", 'H');
//     // ft_printf("%5c\n", 'H');
//     // ft_printf("%-5c\n", 'H');

//     // printf("+++++++++++++++++++++++++++++\n");
//     // printf("%s\n", "Hello");
//     // printf("%7s\n", "Hello");
//     // printf("%5.3s\n", "Hello");
//     // printf("%-5.3s\n", "Hello");
//     // printf("%5.7s\n", "Hello");
//     // printf("%7.7s\n", "Hello");
//     // printf("%-5s\n", "Hello");
//     // printf("-----------------------------\n");
//     // ft_printf("%s\n", "Hello");
//     // ft_printf("%7s\n", "Hello");
//     // ft_printf("%5.3s\n", "Hello");
//     // ft_printf("%-5.3s\n", "Hello");
//     // ft_printf("%5.7s\n", "Hello");
//     // ft_printf("%7.7s\n", "Hello");
//     // ft_printf("%-5s\n", "Hello");

//     // printf("+++++++++++++++++++++++++++++\n");
//     // printf("%05.2d\n", -2);
//     // printf("%05.d\n", -2);
//     // printf("%5d\n", -20);
//     // printf("%05.10d\n", -211110);
//     // printf("%10.5d\n", -211110);
//     // printf("%.5d\n", 20);
//     // printf("%-5d\n", 20);
//     // printf("%+05d\n", 0);
//     // printf("%+010.5d\n", 20);
//     // printf("%010.5d\n", 20);
//     // printf("% d\n", -20);
//     // printf("%  d\n", 20);
//     // printf("-----------------------------\n");
//     // ft_printf("%05.2d\n", -2);
//     // ft_printf("%05.d\n", -2);
//     // ft_printf("%5d\n", -20);
//     // ft_printf("%05.10d\n", -211110);
//     // ft_printf("%10.5d\n", -211110);
//     // ft_printf("%.5d\n", 20);
//     // ft_printf("%-5d\n", 20);
//     // ft_printf("%+05d\n", 0);
//     // ft_printf("%+010.5d\n", 20);
//     // ft_printf("%010.5d\n", 20);
//     // ft_printf("% d\n", -20);
//     // ft_printf("%  d\n", 20);

//     // printf("+++++++++++++++++++++++++++++\n");
//     // int a = 2;
//     // printf("%p\n", &a);
//     // printf("%-3.p\n", &a);
//     // printf("%30p\n", &a);
//     // printf("%-5p\n", &a);
//     // printf("-----------------------------\n");
//     // ft_printf("%p\n", &a);
//     // ft_printf("%-3.p\n", &a);
//     // ft_printf("%30p\n", &a);
//     // ft_printf("%-5p\n", &a);

//     // printf("+++++++++++++++++++++++++++++\n");
//     // printf("%05u\n", 2);
//     // printf("%05.u\n", 2);
//     // printf("%5u\n", 20);
//     // printf("%.12u\n", -3);
//     // printf("%10.5u\n", 211110);
//     // printf("%.5u\n", 20);
//     // printf("%-5u\n", 20);
//     // printf("%010.5u\n", 20);
//     // printf("-----------------------------\n");
//     // ft_printf("%05u\n", 2);
//     // ft_printf("%05.u\n", 2);
//     // ft_printf("%5u\n", 20);
//     // ft_printf("%.12u\n", -3);
//     // ft_printf("%10.5u\n", 211110);
//     // ft_printf("%.5u\n", 20);
//     // ft_printf("%-5u\n", 20);
//     // ft_printf("%010.5u\n", 20);

//     // printf("+++++++++++++++++++++++++++++\n");
//     // printf("%d\n", printf("%x\n", 0));
//     // printf("%d\n", printf("%5x\n", 20));
//     // printf("%d\n", printf("%5.3x\n", 20));
//     // printf("%d\n", printf("%5.7x\n", 20));
//     // printf("%d\n", printf("%05.3x\n", 20));
//     // printf("%d\n", printf("%-5x\n", 20));
//     // printf("%d\n", printf("%#5x\n", 20));
//     // printf("%d\n", printf("%05x\n", 20));
//     // printf("%d\n", printf("%#05.3x\n", 20));
//     // printf("%d\n", printf("%#5.3x\n", 20));
//     // printf("%d\n", printf("%#5.x\n", 20));
//     // printf("%d\n", printf("%#5.x\n", 20000));
//     // printf("-----------------------------\n");
//     // printf("%d\n", ft_printf("%x\n", 0));
//     // printf("%d\n", ft_printf("%5x\n", 20));
//     // printf("%d\n", ft_printf("%5.3x\n", 20));
//     // printf("%d\n", ft_printf("%5.7x\n", 20));
//     // printf("%d\n", ft_printf("%05.3x\n", 20));
//     // printf("%d\n", ft_printf("%-5x\n", 20));
//     // printf("%d\n", ft_printf("%#5x\n", 20));
//     // printf("%d\n", ft_printf("%05x\n", 20));
//     // printf("%d\n", ft_printf("%#05.3x\n", 20));
//     // printf("%d\n", ft_printf("%#5.3x\n", 20));
//     // printf("%d\n", ft_printf("%#5.x\n", 20));
//     // printf("%d\n", ft_printf("%#5.x\n", 20000));

//     // printf("%d\n", printf(" NULL %s NULL \n", NULL));
//     // ft_printf(" NULL %s NULL \n", NULL);
//     // printf(" %#lx \n", LONG_MIN);
//     // printf(" %#x \n", INT_MIN);
//     // ft_printf(" %#x \n", INT_MIN);
//     // ft_printf(" %#x \n", LONG_MIN);

//     // printf("%d\n", printf(" %-2d \n", -1));
//     // printf("%d\n", ft_printf(" %-2d \n", -1));

//     // printf("%01.X\n", 0);
//     // ft_printf("%01.X\n", 0);

//     // printf("%03.0u\n", 0);
//     // ft_printf("%03.0u\n", 0);
//     // char *null_str = 0;
//     // printf("%7s\n", null_str);
//     // ft_printf("%7s\n", null_str);

// 	// printf("%d\n", printf("%-2x\n", 20));
//     // printf("%d\n", printf("%-#2x\n", 20));

// 	// printf("%d\n", ft_printf("%-2x\n", 20));
//     // printf("%d\n", ft_printf("%-#2x\n", 20));
// 	ft_printf("%-0s\n", "");
// 	printf("%-0s\n", "");
//     return (0);
// }