/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzatar <mzatar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:47:43 by mehdi             #+#    #+#             */
/*   Updated: 2020/08/1 by mzatar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	is_single_format (const char *s)
{
	int count;

	count = 0;
	while (*s)
	{
		if (*(s - 1) != '%' && *s == '%' && *(s + 1) == '\0')
			count++;
		s++;
	}
	if (count == 1)
		return (1);
	return(0);
}

int	count_format (const char *s)
{
	int	nbr_type;
	int count_format;

	count_format = 0;
	if (s == NULL)
		return (0);
	nbr_type = 0;

	if (is_single_format(s + 1))
		return (0);
	while (*s)
	{
		if (*s == '%')
		{
			if (*(s + 1) == '%')
				s++;
			if (*(s + 1) == 'd' || *(s + 1) == 'i' || *(s + 1) == 's'|| *(s + 1) == 'c')
				nbr_type++;
			if (*(s + 1) == 'x'|| *(s + 1) == 'X' || *(s + 1) == 'u')
				nbr_type++;
			if (*(s + 1) == '0')
			{
				nbr_type++;
				s++;
				if (*(s + 1) == '*')
					nbr_type++;
				if (*(s + 1) == '.')
					nbr_type++;
			}
			if (*(s + 1) == '.')
			{
				s++;
				while ((ft_isdigit(*(s + 1))))
				{
					if(*(s + 2) == 's')
					{
						nbr_type++;
						s++;
					}
				s++;
				}
			}
		}
		s++;
	}
	return (nbr_type);
}

int	write_zero_flag (int count_zero, int nbr)
{
	int	length;
	
	length = count_zero;
	while (count_zero > 1)
	{
		ft_putnbr(0);
		count_zero--;
	}
	ft_putnbr(nbr);
	return (length);
}

int		return_char_arg (va_list ap)
{
	char *tmp;
	int res;

	res = 0;
	if (!ap)
		return (0);
	if ((!(tmp = ft_strdup(va_arg(ap, char *)))))
	{
		res = ft_putstr(tmp);
		return (0);
	}
	res = ft_putstr(tmp);
	free(tmp);
	return (res);
}

char *zero_padding_1 (const char *s, va_list ap)
{
	int	count_zero;
	int	nbr;
	int res;

	res = 0;
	count_zero = 0;
	nbr = 0;
	if (*(s + 1) == 'd' || *(s + 1) == 'i')
	{
		count_zero = va_arg(ap, int);
		nbr = va_arg(ap, int);
		res += write_zero_flag(count_zero, nbr);
		return ((char *)(s + 2));
	}
	if (*(s + 1) == 'u')
	{
		count_zero = va_arg(ap, int);
		nbr = va_arg(ap, unsigned int);
		res += write_zero_flag(count_zero, nbr);
		return ((char *)(s + 2));
	}
	return ((char *)s);	
}

char *zero_padding_2 (const char *s)
{
	char	*convert;
	int		i;

	i = 0;
	if (!(convert = malloc(sizeof(*s) * (ft_strlen((char *)(s)+ 1)))))
		return (NULL);
	while (*(s +1) != 'd' && *(s +1) != 'i' && *(s +1) != 'u')
	{
		*(convert + i) = *(s + 1);
		s++;
		i++;
	}
	*(convert + i) = '\0';
	return (convert);
}

int	write_format (const char s, va_list ap)
{
	int res;

	res = 0;
	if (s == 's')
		return (res = return_char_arg(ap));
	if (s == 'd'|| s == 'i')
		return (res = ft_putnbr(va_arg(ap, int)));
	if (s == 'c')
		return (res = ft_putchar(va_arg(ap, int)));
	if (s == 'u')
		return(res = ft_writenbr_base(va_arg(ap, unsigned int), 10, "012345678910"));
	if (s == 'x')
		return(res = ft_writenbr_base(va_arg(ap, unsigned int), 16, "0123456789abcdef"));
	if (s == 'X')
		return(res = ft_writenbr_base(va_arg(ap, unsigned int), 16, "0123456789ABCDEF"));
	return (0);
}

char *number_in_string(const char *s)
{
	int buf;
	int i;
	char *tmp;

	buf = 256;
	i = 0;
	if (!(tmp = malloc(sizeof(char) * buf + 1)))
		return (NULL);
	while (ft_isdigit(s[i]))
		i++;
	if (i > buf)
		return (NULL);
	i = 0;
	while (ft_isdigit(s[i]))
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int write_spaces(const char *s, va_list ap, int neg)
{
	int	count_spaces;
	int	length;
	int res;
	char *tmp;

	res = 0;
	length = 0;
	if (!s)
		return (-1);
	count_spaces = ft_atoi(s);
	if(!(tmp = ft_strdup(va_arg(ap, char *))))
		return (-1);
	length = ft_strlen(tmp);
	if (neg == 0)
	{
		if (length >= count_spaces)
		{
			ft_putstr(tmp);
			free(tmp);
			return(length);
		}
		while (res < (count_spaces - length))
			res += ft_putchar(' ');
		ft_putstr(tmp);
		free(tmp);
		return (count_spaces);
	}
	if (neg == 1)
	{
		ft_putstr(tmp);
		free(tmp);
		res += length;
		if (length >= count_spaces)
			return (res);
		while (count_spaces > res)
			res += ft_putchar(' ');
	}
	return (res);
}

int		ft_tronc(char *s, va_list ap)
{
	int nbr;
	int	res;
	char *tmp;
	
	res = 0;
	if(!(tmp = ft_strdup(va_arg(ap, char *))))
		return(0);
	nbr = ft_atoi(s);
	while (res < nbr && *tmp)
	{
		res += ft_putchar(*tmp);
		tmp++;
	}
	return (res);
}

int write_spaces_2(const char *s, int neg, char *tmp)
{
	int	count_spaces;
	int res;
	int length;

	res = 0;
	if (!s)
		return (-1);
	length = ft_strlen((char *)s);
	count_spaces = ft_atoi(tmp);
	if (neg == 0)
	{
		while (res < count_spaces - 1)
			res += ft_putchar(' ');
		res += ft_putchar((char)*(s + (length - 1)));
	}
	if (neg == 1)
	{
		res += ft_putchar((char)*(s + (length - 1)));
		while (res < count_spaces)
			res += ft_putchar(' ');
	}
	return (res);
}

int	write_zero_flag_2 (const char *s)
{
	int count_zero;
	int	res;
	int	i;
	char *tmp;

	count_zero = 0;
	res = 0;
	if (!(tmp = malloc(sizeof(char) * ft_strlen((char *)s))))
		return(0);
	i= 0;
	while (ft_isdigit(s[i]) && s[i] != '%')
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	count_zero = ft_atoi(tmp);
	i = ft_strlen(tmp);
	free(tmp);
	while (count_zero > 1)
	{
		res += ft_putnbr(0);
		count_zero--;
	}
	if (*(s + i) == '%')
	{
		res += ft_putchar('%');
		i++;
	}
	return (res);
}

int		check_single_convers(const char *s)
{
	int res;
	int	neg;
	char *tmp;

	res = 0;
	neg = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s != '%')
			res += ft_putchar(*s);
		else if (*(s + 1) == '%')
		{
			res += ft_putchar('%');
			s++;
		}
		else if (*(s + 1) == '-')
		{
			neg = 1;
			s++;
			while (*s == '-')
				s++;
		}
		else if (ft_isdigit(*(s + 1)))
		{
			tmp = ft_strdup((char *)number_in_string(s));
			res += write_spaces_2(s, neg, tmp);
			s += ft_strlen(tmp);
			free(tmp);
		}
		else if (*(s + 1) == '0')
			return(res += write_zero_flag_2(s + 1)); 
		s++;
	}
	return (res);
}

// char *check_convers(const char *s, va_list ap)
// {
// 	char *tmp;
// 	int neg;
// 	int res;
	
// 	res = 0;
// 	neg = 0;
// 	if (*s == '%')
// 	{
// 		ft_putchar('%');
// 		return (res += 1);
// 	}
// 	if (*s == '-')
// 	{
// 		neg = 1;
// 		s++;
// 		while (*s == '-')
// 			s++;
// 	}
// 	if (ft_isdigit(*s))
// 	{
// 		tmp = ft_strdup((char *)number_in_string(s));
// 		res += write_spaces(tmp, ap, neg);
// 		s += ft_strlen(tmp);
// 		free(tmp);
// 		return ((char *)s);
// 	}
// 	if (*s == '.')
// 	{
// 		tmp = ft_strdup((char *)number_in_string(s + 1));
// 		res += ft_tronc(tmp, ap);
// 		s += ft_strlen(tmp) + 1;
// 		free(tmp);
// 		return((char *)s);
// 	}
// 	if (*s == '0')
// 	{
// 		if (*(s + 1) == '*')
// 			return (zero_padding_1((s + 1), ap));
// 		if (*(s + 1) == '.')
// 		{
// 			tmp = ft_strdup(zero_padding_2(s + 1));
// 			res += write_zero_flag(ft_atoi(tmp), va_arg(ap, int)+ ft_strlen(tmp) - 1);
// 			s += (2 + ft_strlen(tmp));
// 			free(tmp);
// 			return ((char *)(s));
// 		}
// 	}
// 	else
// 	{
// 		res += write_format((*s), ap);
// 		return ((char *)(s));
// 	}
// 	return ((char *)s);
// }

int	find_format(const char *s, va_list ap, int nbr_type)
{
	int	res;
	int	neg;
	char *tmp;

	res = 0;
	neg = 0;
	if (!s)
		return (-1);
	while (*s && nbr_type > 0)
	{
		if (*s != '%')
			res += ft_putchar(*s);
		else if (*(s + 1) == '%')
		{
			res += ft_putchar('%');
			nbr_type--;
		}
		else if (*(s + 1) == '-')
		{
			neg = 1;
			while (*s == '-')
				s++;
		}
		else if (ft_isdigit(*(s + 1)))
		{
			tmp = ft_strdup((char *)number_in_string(s));
			res += write_spaces(tmp, ap, neg);
			s += ft_strlen(tmp) + 1;
			free(tmp);
			nbr_type--;
		}
		else if (*(s + 1) == '.')
		{
			tmp = ft_strdup((char *)number_in_string(s + 1));
			res += ft_tronc(tmp, ap);
			s += ft_strlen(tmp);
			nbr_type--;
		}
		else if (*(s + 1) == '0')
		{
			if (*(s + 2) == '*')
			{
				s = zero_padding_1((s + 1), ap);
				nbr_type--;
			}
			if (*(s + 2) == '.')
			{
				tmp = ft_strdup(zero_padding_2(s + 1));
				res += write_zero_flag(ft_atoi(tmp), va_arg(ap, int)+ ft_strlen(tmp) - 1);
				s += (2 + ft_strlen(tmp));
				free(tmp);
				nbr_type--;
			}
		}
		else
		{
			res += write_format(*(s + 1), ap);
			s++;
			nbr_type--;
		}
		//s = check_convers((s + 1), ap);
		s++;
	}
	return (res);
}