/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:25:39 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Program name     libftprintf.a
Turn in files       Makefile, *.h, * / *.h, *.c, * / *.c
Makefile            NAME, all, clean, fclean, re
External functs.    malloc, free, write, va_start, va_arg, va_copy, va_end
Libft authorized    Yes
Description         Write a library that contains ft_printf() (mimic printf()*/

/* va_list: This macro declares a variable to hold the list of arguments.
va_start: initializes the va_list variable to point to the first variable argt.
va_arg: retrieves the next argt from the list, using the type info provided.
va_end: cleans up the va_list var after you're done processing the argts.*/

#include "libft.h"

void	wrong_format(const char *ag0)
{
	int		i;
	char	*warning;

	warning = "\nWarning: conversion lacks type at end of format [-Wformat=]\n";
	i = 0;
	while (ag0[i])
	{
		if (ag0[i] == '%')
		{
			if (!ft_strchr("cspdiuxX%# +", ag0[i + 1]))
			{
				ft_putstr_fd(warning, 1);
				i += 2;
			}
			else if (ag0[i + 1] == '\0')
			{
				ft_putstr_fd(warning, 2);
				i++;
			}
		}
		i++;
	}
}

int	call_function(const char *ag0, va_list ap, int length)
{
	int	i;

	i = 0;
	while (ag0[i]) 
	{
		if (ag0[i] == '%') 
		{
			i++;
			length += specifier_1(ag0, ap, i) + specifier_2(ag0, ap, i)
				+ specifier_3(ag0, ap, i) + specifier_4(ag0, ap, i) 
				+ specifier_5(ag0, ap, i);
			i++;
		}
		else 
		{
			ft_putchar_fd(ag0[i], 1);
			length++;
			i++;
		}
	}
	return (length);
}

int	ft_printf(const char *ag0, ...)
{
	va_list	ap;
	int		length;

	if (ag0 == 0)
		return (-1);
	length = 0;
	va_start(ap, ag0);
	length = call_function(ag0, ap, length);
	va_end(ap);
	return (length);
}
