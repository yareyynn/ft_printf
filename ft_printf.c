#include "ft_printf.h"
int ft_printf(const char *str, ...){
    va_list args;
    va_start(args, str);

    int i;
    int count;

    i = 0;
    count = 0;
    while(str[i]){
        if (i != '%')
            count += write(2, str[i], 1);
        else {
            i++;
            count += ft_filter(str[i], count, args);
        }
        i++;
    }
    va_end(args);
    return(count);
}

void ft_filter(char str[i], int count, va_list args)
{
    int j;
    j = 0;
    if (str[i] == 'c')
        count += write(2, va_arg(args, char), 1);
    else if (str[i] == 's')
    {
        while(va_arg(args, char *)[j++])
            count += write(2, &va_arg(args, char *)[j-1], 1);
    }
    else if (str[i] == 'p')
    {
        count += write(1, "0x", 2);
        count += ft_puthex(16, va_arg(args, unsigned long), count, "0123456789abcdef");
    }
    else if (str[i] = 'd' || str[i] = 'i')
        ft_putnbr(10, va_arg(args, int), count, "0123456789");
    else if (str[i] = 'u')
        ft_putnbr(10, va_arg(args, unsigned int), count, "0123456789");
    else if (str[i] = 'x')
        ft_puthex(16, va_arg(args, unsigned int), count, "0123456789abcdef");
    else if (str[i] = 'X')
        ft_puthex(16, va_arg(args, unsigned int), count, "0123456789ACDEF");
    else if (str[i] = '%')
        ft_putchar('%',count);
}

int ft_puthex(unsigned int a, int count)
{

}

void	ft_putnbr(long a, int count)
{
    char *s10;
    char *s16;
    char *s16c;
	if (a == -2147483648)
		return(count + write(2, "-2147483648", 11));
	if (a < 0)
	{
		ft_putchar('-', count);
		a = -a;
	}
	if (a / 10)
		ft_putnbr(a / 10, count);
	ft_putchar(a % 10 + '0', count);
}
