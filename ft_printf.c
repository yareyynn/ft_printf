#include "ft_printf.h"

static int	ft_putbase(char c, long long x, int *count, char *s)
{
	int	a;

	if (c == 'd' || c == 'i')
	{
		a = 10;
		if (x < 0)
		{
			*count += write(1, "-", 1);
			x = -x;
		}
	}
	else if (c == 'p')
	{
		*count += write(1, "0x", 2);
		a = 16;
	}
	else
		a = 16;

	if (x / a)
		ft_putbase(c, x / a, count, s);
	*count += write(1, &s[x % a], 1);
	return *count;
}

static void	ft_filter(char c, int *count, va_list args)
{
	char	*str;

	if (c == 'c')
	{
		c = va_arg(args, int);
		*count += write(1, &c, 1);
	}
	else if (c == 's')
	{
		str = va_arg(args, char *);
		while (*str)
			*count += write(1, str++, 1);
	}
	else if (c == 'p')
		ft_putbase(c, va_arg(args, unsigned long), count, "0123456789abcdef");
	else if (c == 'd' || c == 'i')
		ft_putbase(c, va_arg(args, int), count, "0123456789");
	else if (c == 'u')
		ft_putbase(c, va_arg(args, unsigned int), count, "0123456789");
	else if (c == 'x' || c == 'X')
		ft_putbase(c, va_arg(args, unsigned int), count, 
			(c == 'x' ? "0123456789abcdef" : "0123456789ABCDEF"));
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
