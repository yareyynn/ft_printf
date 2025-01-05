/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakarya <ysakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:13:36 by ysakarya          #+#    #+#             */
/*   Updated: 2025/01/06 00:13:37 by ysakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putbase(char c, long long x, int *count, char *s)
{
	int	a;

	if (c == 'd' || c == 'i' || c == 'u')
	{
		a = 10;
		if( c == 'd' || c == 'i')
		{
			if (x < 0)
			{
				*count += write(1, "-", 1);
				x = -x;
			}
		}
	}
	else
		a = 16;
	if (x / a)
		ft_putbase(c, x / a, count, s);
	*count += write(1, &s[x % a], 1);
}

static void ft_formatp(char c, unsigned long x, int *count)
{
	if (x == 0)
		*count += write(1, "nil", 3);
	else
	{
		*count += write(1, "0x", 2);
		ft_putbase(c, x, count, "0123456789abcdef");
	}
}

static void	ft_filter(char c, int *count, va_list args)
{
	char *str;

	if (c == 'c')
	{
		c = va_arg(args, int);
		*count += write(1, &c, 1);
	}
	else if (c == 's')
	{
		str = va_arg(args, char*);
		while (*str)
			*count += write(1, str++, 1);
	}
	else if (c == 'p')
		ft_formatp(c, va_arg(args, unsigned long), count);
	else if (c == 'd' || c == 'i')
		ft_putbase(c, va_arg(args, int), count, "0123456789");
	else if (c == 'u')
		ft_putbase(c, va_arg(args, unsigned int), count, "0123456789");
	else if (c == 'x')
		ft_putbase(c, va_arg(args, unsigned int), count, "0123456789abcdef");
	else if (c == 'X')
		ft_putbase(c, va_arg(args, unsigned int), count, "0123456789ABCDEF");
	else if (c == '%')
		*count += write(1, &c, 1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	va_start(args, str);
	count = 0;
	while (*str)
	{
		if (*str == '%' && *(++str))
			ft_filter(*str, &count, args);
		else
			count += write(1, str, 1);
		str++;
	}
	va_end(args);
	return count;
}
