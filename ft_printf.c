/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzatar <mzatar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:17:27 by mehdi             #+#    #+#             */
/*   Updated: 2020/08/21 16:57:46 by mzatar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	check_errors(const char *s)
{
	if (s == NULL)
		return (0);
	return (1);
}

int ft_printf(const char *s, ...)
{
	va_list		ap;
	int			nbr_type;
	int			size_printed;
	
	size_printed = 0;
	va_start(ap, s);
	if (check_errors(s) == -1)
		return (0);
	nbr_type = count_format(s);
	if (nbr_type == 0)
		return (size_printed = check_single_convers(s));
	size_printed = find_format(s, ap, nbr_type);
	va_end(ap);
	return (size_printed);
}