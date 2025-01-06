/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakarya <ysakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:13:36 by ysakarya          #+#    #+#             */
/*   Updated: 2025/01/06 05:33:38 by ysakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putbase(char c, unsigned long x, int *count, char *s)
{
	int	a;

	a = 0;
	while (s[a])
		a++;
	if (c == 'd' || c == 'i' || c == 'u')
	{
		if (c == 'd' || c == 'i')
		{
			if ((int) x < 0)
			{
				*count += write(1, "-", 1);
				x = -x;
			}
		}
	}
	else if (c == 'p' || c == 'x' || c == 'X')
	{
		if (c == 'p')
			*count += write(1, "0x", 2);
	}
	if (x / a)
		putbase('y', x / a, count, s);
	*count += write(1, &s[x % a], 1);
}

static void	ft_putstr(char *s, int *count)
{
	if (!s)
		*count += write(1, "(null)", 6);
	else
	{
		while (*s)
			*count += write(1, s++, 1);
	}
}

static void filterp(unsigned long t, int *count)
{
	if (t != 0)
		putbase('p', t, count, "0123456789abcdef");
	else
		*count += write(1, "(nil)", 5);
}

static void	filter(char c, int *count, va_list args)
{
	if (c == 'c')
	{
		c = va_arg(args, int);
		*count += write(1, &c, 1);
	}
	else if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (c == 'p')
		filterp(va_arg(args, unsigned long), count);
	else if (c == 'd' || c == 'i')
		putbase(c, va_arg(args, int), count, "0123456789");
	else if (c == 'u')
		putbase(c, va_arg(args, unsigned int), count, "0123456789");
	else if (c == 'x')
		putbase(c, va_arg(args, unsigned int), count, "0123456789abcdef");
	else if (c == 'X')
		putbase(c, va_arg(args, unsigned int), count, "0123456789ABCDEF");
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
			filter(*str, &count, args);
		else
			count += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (count);
}
