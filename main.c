#include "libftprintf.h"

int main (int argc, char **argv)
{
	(void)argc;
	(void)argv;

	// char	c = 'a';
	// int		d = 2147483647;
	// int		e = -2147483648;
	// int		i = 8;
	// int		j = -12;
	// int		k = 123456789;
	// int		l = 0;
	// int		m = -12345678;
	// /char	*p = "abcdefghijklmnop";

	// printf("size = %d \n",ft_printf("%8i, %5d, %8d, %8d, %8d, %8d, %8d, %8d", i, j, k, l, m, c, e, d));
	// printf("size = %d \n",printf("%8i, %5d, %8d, %8d, %8d, %8d, %8d, %8d", i, j, k, l, m, c, e, d));

	//printf("size = %d \n",printf("%7.3s%7.3s", "hello", "world"));
	printf("%7.7s", "world");
	printf("\n");
	ft_printf("%7.7s", "world");
	//printf("size = %d \n",ft_printf("%-8.5i", 0));
	return (0);
}