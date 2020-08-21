/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzatar <mzatar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:54:40 by mehdi             #+#    #+#             */
/*   Updated: 2020/08/18 16:14:15 by mzatar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_putchar(char c)
{
	int res;

	res = 0;
	write(1, &c, 1);
	res += 1;
	return (res);
}

int		ft_putstr(char *s)
{
	int size; 

	size = ft_strlen(s);
	if (!s)
		return (0);
	while (*s)
		ft_putchar(*s++);
	return(size);
}

int		ft_putnbr(int n)
{
	long	nbr;
	int		res;

	res = 0;
	nbr = (long)n;
	if (nbr < 0)
	{
		res += ft_putchar('-');
		nbr *= -1;
	}
	if (nbr >= 10)
		res += ft_putnbr(nbr / 10);
	res += ft_putchar(nbr % 10 + 48);
	return (res);
}

int		base_error(char *base)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		j = i + 1;
		if (base[i] < 32 || base[i] > 126 || base[i] == '+' || base[i] == '-')
			return (0);
		while (base[j])
		{
			if (base[i] == base[i + 1])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_writenbr_base(unsigned int nbr, int base_size, char *base)
{
	unsigned int	nbr2;
	int				res;

	res = 0;
	nbr2 = nbr;
	if (nbr2 < 0)
	{
		nbr2 = nbr2 * - 1;
		res += ft_putchar('-');
	}
	if (nbr2 / base_size)
	{
		res += ft_writenbr_base(nbr2 / base_size, base_size, base);
	}
	res += ft_putchar(base[nbr2 % base_size]);
	return (res);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int base_size;

	base_size = 0;
	if (base_error(base))
	{
		while (base[base_size] != '\0')
		{
			base_size++;
		}
		ft_writenbr_base(nbr, base_size, base);
	}
}

char		*ft_strdup(const char *s1)
{
	int		size;
	int		i;
	char	*cpy;

	if (!s1)
		return (NULL);
	size = ft_strlen((char *)s1);
	if (!(cpy = malloc((size + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(cpy + i) = *(s1 + i);
		i++;
	}
	*(cpy + i) = '\0';
	return (cpy);
}

static int		is_space(char str)
{
	if (str == '\t' || str == '\n' || str == '\r'
	|| str == '\v' || str == '\f' || str == 32)
		return (1);
	return (0);
}

static int		ft_result(const char *str, unsigned long long res,
int sign, int i)
{
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		if ((res > 922337203685477580 || (res == 922337203685477580))
		&& sign == 1)
			return (-1);
		else if ((res > 922337203685477580 || (res == 922337203685477580))
		&& sign == -1)
			return (0);
		res = (res * 10) + (unsigned long long)(str[i] - '0');
		i++;
	}
	return (res * sign);
}

int				ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	return (ft_result(str, res, sign, i));
}

int	ft_isdigit(int c)
{
	if ((c > '0' && c <= '9'))
		return (1);
	return (0);
}

static int			nbr_length(int n)
{
	int		length;
	long	nb;

	length = 1;
	nb = n;
	if (nb < 0)
	{
		length++;
		nb *= -1;
	}
	while (nb >= 10)
	{
		length++;
		nb /= 10;
	}
	return (length);
}

char				*ft_itoa(int n)
{
	long	nbr;
	int		index;
	char	*str;

	if (!(str = malloc(sizeof(char) * (nbr_length(n) + 1))))
		return (NULL);
	nbr = (long)n;
	if (n < 0)
		str[0] = '-';
	if (nbr < 0)
		nbr *= -1;
	index = 0;
	str[nbr_length(n) - index++] = '\0';
	while (nbr >= 10)
	{
		str[nbr_length(n) - index++] = (nbr % 10) + 48;
		nbr /= 10;
	}
	str[nbr_length(n) - index++] = nbr + 48;
	return (str);
}