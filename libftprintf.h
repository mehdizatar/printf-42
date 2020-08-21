#	ifndef LIBFTPRINTF_H
# 	define LIBFTPRINTF_H

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

int		ft_strlen(char *str);
int		ft_putstr(char *s);
int		ft_putchar(char c);
int		ft_putnbr(int n);
int		check_errors(const char *s);
int		count_format (const char *s);
int		write_format (const char s, va_list ap);
int		find_format(const char *s, va_list ap, int nbr_type);
int		ft_writenbr_base(unsigned int nbr, int base_size, char *base);
char	*zero_padding_1 (const char *s, va_list ap);
char 	*zero_padding_2 (const char *s);
int		write_zero_flag (int count_zero, int nbr);
char 	*check_convers(const char *s, va_list ap);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
int		base_error(char *base);
void	ft_putnbr_base(int nbr, char *base);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
int 	ft_printf(const char *s, ...);
int 	write_spaces(const char *s, va_list ap, int neg);
char	*number_lengthnumber_in_string(const char *s);
int		ft_isdigit(int c);
int		ft_tronc(char *s, va_list ap);
char 	*number_in_string(const char *s);
int		return_char_arg (va_list ap);
int		ft_strcmp(char *s1, char *s2);
int		write_zero_flag_2 (const char *s);
int 	write_spaces_2(const char *s, int neg, char *tmp);
int		check_single_convers(const char *s);
int		write_spaces_nbr(const char *s, int neg, va_list ap);
int		ft_tronc_nbr(const char	*s, va_list ap);
char	*ft_itoa(int n);
int		write_nbr_left_right(const char *s, char *s0, va_list ap, int neg);
char	*return_ap (const char s, va_list ap);

#	endif