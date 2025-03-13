/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:18:44 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* additionnal function to print the values */

#include "libft.h"

void	ft_putunbr_fd(unsigned int nb, int fd)
{
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}

void	ft_putnhex_up_fd(unsigned int nb, int fd)
{
	char	*base;
	char	digit;

	digit = '0';
	base = "0123456789ABCDEF";
	if (nb >= 16)
	{
		ft_putnhex_up_fd(nb / 16, fd);
		ft_putnhex_up_fd(nb % 16, fd);
	}
	else
	{
		digit = base[nb];
		write(fd, &digit, 1);
	}
}

void	ft_putnhex_lo_fd(unsigned int nb, int fd)
{
	char	*base;
	char	digit;

	digit = '0';
	base = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_putnhex_lo_fd(nb / 16, fd);
		ft_putnhex_lo_fd(nb % 16, fd);
	}
	else
	{
		digit = base[nb];
		write(fd, &digit, 1);
	}
}

void	ft_putnhex_lo_long_fd(unsigned long nb, int fd)
{
	char	*base;
	char	digit;

	digit = '0';
	base = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_putnhex_lo_long_fd(nb / 16, fd);
		ft_putnhex_lo_long_fd(nb % 16, fd);
	}
	else
	{
		digit = base[nb];
		write(fd, &digit, 1);
	}
}
