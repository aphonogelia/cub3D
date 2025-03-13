/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:09:29 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* we handle the specifiers - we print and return the length of the print */

#include "libft.h"

int	specifier_1(const char *a0, va_list ap, int i)
{
	int		length;
	char	c;

	length = 0;
	if (a0[i] == 'c')
	{
		c = va_arg(ap, int);
		ft_putchar_fd(c, 1);
		length = 1;
	}
	return (length);
}

int	specifier_2(const char *a0, va_list ap, int i)
{
	int		length;
	char	*str;

	length = 0;
	if (a0[i] == 's')
	{
		str = va_arg(ap, char *);
		if (str)
		{
			ft_putstr_fd(str, 1);
			length = ft_strlen(str); 
		}
		else if (str == (char *) NULL) 
		{
			ft_putstr_fd("(null)", 1);
			length = 6;
		}
	}
	return (length);
}

int	specifier_3(const char *a0, va_list ap, int i)
{
	int		length;
	void	*address;

	length = 0;
	if (a0[i] == 'p')
	{
		address = va_arg(ap, void *);
		if (address == 0)
		{
			ft_putstr_fd("(nil)", 1);
			return (5);
		}
		else
		{
			ft_putstr_fd("0x", 1);
			ft_putnhex_lo_long_fd((uintptr_t)address, 1);
			length = (2 + ft_ulonglen((uintptr_t)address, 16));
		}
	}
	else if (a0[i] == '%')
	{
		ft_putchar_fd('%', 1);
		length = 1; 
	}
	return (length);
}

int	specifier_4(const char *a0, va_list ap, int i)
{
	int				length;
	int				digit;
	unsigned int	u;

	length = 0;
	if (a0[i] == 'd' || a0[i] == 'i')
	{
		digit = va_arg(ap, int);
		ft_putnbr_fd(digit, 1);
		if (digit == -2147483648)
			length = 11;
		else
			length = ft_intlen(digit, 10); 
	}
	else if (a0[i] == 'u')
	{
		u = va_arg(ap, unsigned int );
		ft_putunbr_fd(u, 1);
		length = ft_uintlen(u, 10); 
	}
	return (length);
}

int	specifier_5(const char *a0, va_list ap, int i)
{
	int				length;
	unsigned int	hexalow;
	unsigned int	hexaupp;

	length = 0;
	if (a0[i] == 'x')
	{
		hexalow = va_arg(ap, unsigned int);
		ft_putnhex_lo_fd(hexalow, 1);
		length = ft_uintlen(hexalow, 16); 
	}
	else if (a0[i] == 'X')
	{
		hexaupp = va_arg(ap, unsigned int);
		ft_putnhex_up_fd(hexaupp, 1);
		length = ft_uintlen(hexaupp, 16); 
	}
	return (length);
}
