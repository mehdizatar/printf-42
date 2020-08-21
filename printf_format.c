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

int	is_a_nbr_convers(const char s)
{
	if (s == 'd' || s == 'i' || s == 'u'|| s == 'X' || s == 'x')
		return(1);
	return (0);
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
			if (*(s + 1) == '-')
				s++;
			if (*(s + 1) == '%')
				s++;
			if (*(s + 1) == 'd' || *(s + 1) == 'i' || *(s + 1) == 's'|| *(s + 1) == 'c')
				nbr_type++;
			if (*(s + 1) == 'x'|| *(s + 1) == 'X' || *(s + 1) == 'u' || *(s + 1) == 'p')
				nbr_type++;
			if (*(s + 1) == '0')
			{
				if (*(s + 2) == '*')
					nbr_type++;
				if (*(s + 2) == '.')
					nbr_type++;
				// while(ft_isdigit(*(s + 2)))
				// {

				// }
				s++;
			}
			if (*(s + 1) == '.')
			{
				s++;
				if (*(s + 2) == 'd' || *(s + 2) == 'i' || *(s + 2) == 'u'|| *(s + 2) == 'X' 
				|| *(s + 2) == 'x' || *(s + 2) == 's')
					nbr_type++;
				while (((ft_isdigit(*(s + 1)) || *(s + 1) == '0') && *s))
				{
					if(*(s + 2) == 's')
					{
						nbr_type++;
						s++;
					}
				s++;
				}
			}
			while ((ft_isdigit(*(s + 1)) || *(s + 1) == '0') && *s)
			{
				if (*(s + 2) == 'd' || *(s + 2) == 'i' || *(s + 2) == 'u'|| *(s + 2) == 'X' 
				|| *(s + 2) == 'x' || *(s + 2) == 's')
					nbr_type++;
				if (*(s + 2) == '.' && ft_isdigit(*(s + 3)))
					nbr_type++;
			s++;
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
	if (*(s + 1) == 'u' || *(s + 1) == 'X' || *(s + 1) == 'x')
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
	while (!(is_a_nbr_convers(*(s + 1))))
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
	if (s == 'p')
	{
		res += ft_putstr("0x");
		res += ft_writenbr_base(va_arg(ap, unsigned int), 16, "0123456789abcdef");
		return (res);
	}
	return (0);
}

char	*return_ap (const char s, va_list ap)
{
	if (s == 'd'|| s == 'i')
		return (ft_itoa(va_arg(ap, int)));
	if (s == 'c')
		return (ft_itoa(va_arg(ap, int)));
	if (s == 'u')
		return(ft_itoa(va_arg(ap, unsigned int)));
	if (s == 'x')
		return(ft_itoa(va_arg(ap, unsigned int)));
	if (s == 'X')
		return(ft_itoa(va_arg(ap, unsigned int)));
	return (0);
}

char *number_in_string(const char *s)
{
	int buf;
	int i;
	char *tmp;;

	buf = 256;
	i = 0;
	if (!(tmp = malloc(sizeof(char) * buf + 1)))
		return (NULL);
	while (ft_isdigit(s[i]) || s[i] == '0')
		i++;
	if (i > buf)
		return (NULL);
	i = 0;
	while (ft_isdigit(s[i]) || s[i] == '0')
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int write_spaces_nbr(const char *s, int neg, va_list ap)
{
	int	count_spaces;
	int	length;
	int res;
	char *tmp;
	va_list cpy;
		
	va_copy(cpy, ap);
	res = 0;
	length = 0;
	tmp = NULL;
	if (!s)
		return (-1);
	length = ft_strlen((char *)number_in_string(s + 1)) + 1;
	count_spaces = ft_atoi((char *)number_in_string(s + 1));
	if (*(s + length) == 'd' || *(s + length)== 'i')
	{
		if(!(tmp = ft_strdup(ft_itoa(va_arg(cpy, int)))))
			return (-1);
		s+= length;
	}
	else if (*(s + length) == 'u' || *(s + length) == 'x' || *(s + length) == 'X')
	{
		if(!(tmp = ft_strdup(ft_itoa(va_arg(cpy, unsigned int)))))
			return (-1);
		s+= length;
	}
	length = ft_strlen(tmp);
	free(tmp);
	if (neg == 0)
	{
		if (length >= count_spaces)
		{
			write_format(*s, ap);
			return(length);
		}
		while (res < (count_spaces - length))
			res += ft_putchar(' ');
		write_format(*s, ap);
		return (count_spaces);
	}
	if (neg == 1)
	{
		write_format(*s, ap);
		res += length;
		if (length >= count_spaces)
			return (res);
		while (count_spaces > res)
			res += ft_putchar(' ');
	}
	return (res);
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

int		ft_tronc_nbr(const char	*s, va_list ap)
{
	int		count_zero;
	int		res;
	int		length;
	char	*tmp;

	count_zero = 0;
	res = 0;
	length = 0;
	tmp = ft_strdup(" ");
	length = ft_strlen((char *)number_in_string(s + 1)) + 1;
	count_zero = ft_atoi((char *)number_in_string(s + 1));
	if (*(s + length) == 'd' || *(s + length)== 'i')
	{
		if(!(tmp = ft_strdup(ft_itoa(va_arg(ap, int)))))
			return (-1);
	}
	else if (*(s + length) == 'u' || *(s + length) == 'x' || *(s + length) == 'X')
	{
		if(!(tmp = ft_strdup(ft_itoa(va_arg(ap, unsigned int)))))
			return (-1);
	}
	length = ft_strlen(tmp);
	if (length >= count_zero)
	{
		res += ft_putstr(tmp);
		free(tmp);
		return (res);
	}
	if (*tmp == '-')
	{
		res += ft_putchar('-');
		tmp++;
		length--;
	}
	while (count_zero - length > 0)
	{
		res += ft_putchar('0');
		count_zero--;
	}
	res += ft_putstr(tmp);
	//free(tmp);
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
	i = 0;
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
		if (*s == '%')
		{
			if (*(s + 1) == '%' && *(s+ 2) == '\0')
				return (res += ft_putchar('%'));
			if (*(s + 1) == '-')
			{
				neg = 1;
				s++;
				while (*s == '-')
					s++;
			}
			if (ft_isdigit(*(s + 1)))
			{
				tmp = ft_strdup((char *)number_in_string(s + 1));
				res += write_spaces_2(s, neg, tmp);
				s += ft_strlen(tmp);
				free(tmp);
			}
			if (*(s + 1) == '0')
				return(res += write_zero_flag_2(s + 2));
		}
		else
			res += ft_putchar(*s);
		s++;
	}
	return (res);
}

int write_zeros_nbr(const char *s, va_list ap)
{
	int	count_zero;
	int	length;
	int res;
	char *tmp;
		
	res = 0;
	length = 0;
	if (!s)
		return (-1);
	length = ft_strlen((char *)number_in_string(s));
	count_zero = ft_atoi((char *)number_in_string(s));
	if(!(tmp = ft_strdup(return_ap(*(s + length), ap))))
		return (-1);
	length = ft_strlen(tmp);
	if (*tmp == '-')
	{
		res += ft_putchar('-');
		tmp++;
		length--;
	}
	if (length >= count_zero)
	{
		res += ft_putstr(tmp);
		return(length);
	}
	while (res < (count_zero - length))
		res += ft_putchar('0');
	ft_putstr(tmp);
	return (count_zero);
}

int	write_nbr_left_right(const char *s, char *s0, va_list ap, int neg)
{
	int	length_total;
	int	nbr_length;
	int	res;
	int	tmp_length;
	char	*tmp;
	
	length_total = 0;
	nbr_length = 0;
	res = 0;
	tmp = NULL;
	nbr_length = ft_atoi((char *)number_in_string(s0));
	length_total = ft_atoi((char *)number_in_string(s + 1));
	s += ft_strlen(number_in_string(s + 1)) + 1;
	if(!(tmp = ft_strdup(return_ap(*s, ap))))
		return (-1);
	tmp_length = ft_strlen(tmp);
	if (neg == 0)
	{
		if (nbr_length > length_total)
		{
			if (*tmp == '-')
			{
				while ((nbr_length - 1) - length_total > 0)
				{
					res += ft_putchar(' ');
					nbr_length--;
				}
				res += ft_putchar('-');
				tmp++;
				tmp_length--;
				nbr_length--;
			}
			else if (*tmp != '-') 
			{
				while (nbr_length - length_total > 0)
				{
					res += ft_putchar(' ');
					nbr_length--;
				}
			}
			while (nbr_length - tmp_length > 0)
			{
				res += ft_putchar('0');
				nbr_length--;
			}
		return (res += ft_putstr(tmp));
		}
		if (*tmp == '-')
		{
			res += ft_putchar('-');
			tmp++;
			tmp_length--;
		}
		while (length_total - tmp_length > 0)
		{
			res += ft_putchar('0');
			length_total--;
		}
		while (length_total - tmp_length > 0)
		{
			res += ft_putchar(' ');
			length_total--;
		}
	return (res += ft_putstr(tmp));
	}
	if (neg >= 1)
	{
		if (nbr_length > length_total)
		{
			if (*tmp == '-')
			{
				res += ft_putchar('-');
				tmp++;
				tmp_length--;
				nbr_length--;
			}
			while (length_total - tmp_length > 0)
			{
				res += ft_putchar('0');
				length_total--;
				nbr_length--;
			}
			res += ft_putstr(tmp);
			while (nbr_length - 1 > 0)
			{
				res += ft_putchar(' ');
				nbr_length--;
			}
		return (res);
		}
		if (*tmp == '-')
		{
			res += ft_putchar('-');
			tmp++;
			tmp_length--;
		}
		while (length_total - tmp_length > 0)
		{
				res += ft_putchar('0');
				nbr_length--;
				length_total--;
		}
		res += ft_putstr(tmp);
		length_total -= res;
		while (length_total > 0)
		{
			res += ft_putchar(' ');
			length_total--;
		}
	return (res);
	}
	free(tmp);
	return (res);
}

int	write_str_left_right(const char *s, char *s0, va_list ap, int neg)
{
	int	length_total;
	int	nbr_length;
	int	res;
	char *tmp;
	(void)ap;
	(void)neg;

	length_total = ft_atoi((char *)number_in_string(s0));
	nbr_length = ft_atoi((char *)number_in_string(s + 1));
	if(!(tmp = ft_strdup(va_arg(ap, char *))))
		return (-1);
	res = 0;
	if (neg == 0)
	{
		if (length_total > nbr_length)
		{
			if (ft_strlen(tmp) < nbr_length)
			{
				while (length_total - ft_strlen(tmp) > 0)
				{
					res += ft_putchar(' ');
					length_total--;
				}
			}
			return (res += ft_putstr(tmp));
		}
		while (length_total - ft_strlen(tmp) > 0)
		{
			res += ft_putchar(' ');
			length_total--;
		}
		while (nbr_length > 0 && *tmp)
		{
			res += ft_putchar(*tmp);
			nbr_length--;
			tmp++;
		}
		free(tmp);
		return(res);
	}
	if (neg >= 1)
	{
		if (length_total > nbr_length)
		{
			if (ft_strlen(tmp) < nbr_length)
			{
				res += ft_putstr(tmp);
				while (length_total - ft_strlen(tmp) > 0)
				{
					res += ft_putchar(' ');
					length_total--;
				}
				return (res);
			}
		}
		while (nbr_length > 0 && *tmp)
		{
			res += ft_putchar(*tmp);
			nbr_length--;
			tmp++;
		}
		while (length_total - nbr_length > 0)
		{
			res += ft_putchar(' ');
			length_total--;
		}
	}
	return (res);
}

int	find_format(const char *s, va_list ap, int nbr_type)
{
	int	res;
	int	neg;
	char *tmp;

	res = 0;
	neg = 0;
	tmp = NULL;
	if (!s)
		return (-1);
	while (*s && nbr_type > 0)
	{
		if (*s != '%')
			res += ft_putchar(*s);
		else 
		{
			if (*(s + 1) == '-')
			{
				neg = 1;
				while (*(s + 1) == '-')
					s++;
			}
			if (*(s + 1) == '%')
			{
				res += ft_putchar('%');
				nbr_type--;
			}
			else if (ft_isdigit(*(s + 1)))
			{
				tmp = ft_strdup((char *)number_in_string(s + 1));
				if (*(s + ft_strlen(tmp) + 1) == '.')
				{
					s += ft_strlen(tmp) + 1;
					while((ft_isdigit(*(s + 1)) || *(s + 1) == 0) && *(s + 2))
					{
						if (is_a_nbr_convers(*(s + 2)))
						{
							res += write_nbr_left_right(s, tmp, ap, neg);
						}
						if (*(s + 2) == 's')
						{
							res += write_str_left_right(s, tmp, ap, neg);
						}
						s++;
					}
				}
				else if (*(s + ft_strlen(tmp) + 1) == 's')
				{
					res += write_spaces(tmp, ap, neg);
					s += ft_strlen(tmp) + 1;
				}
					
				else
				{
					res += write_spaces_nbr(s, neg, ap);
					s += ft_strlen(tmp) + 1;
				}
				free(tmp);
				nbr_type--;
			}
			else if (*(s + 1) == '.')
			{
				tmp = ft_strdup((char *)number_in_string(s + 2));
				if (*(s + ft_strlen(tmp) + 2) == 's')
					res += ft_tronc(tmp, ap);
				else
					res += ft_tronc_nbr(s + 1, ap);
				s += ft_strlen(tmp) + 2;
				free(tmp);
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
				while (ft_isdigit(*(s + 2)))
				{
					if (is_a_nbr_convers(*(s + 3)))
					{
						res += write_zeros_nbr(s + 1, ap);
						s += 1;
						nbr_type--;
					}
					s++;
				}
				s++;
			}
			else
			{
				res += write_format(*(s + 1), ap);
				s++;
				nbr_type--;
			}
		}
		s++;
	}
	return (res);
}