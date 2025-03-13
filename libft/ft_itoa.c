/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:35:51 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Function name ft_itoa Prototype char *ft_itoa(int n);
Return : The string n representing the integer. NULL if the allocation fails.
Allocates (with malloc(3)) and returns a string representing the integer re-
ceived as an argument. Negative numbers must be handled. */

#include "libft.h"

size_t	lengthcalcul(int n)
{
	int		neg;
	size_t	count;

	count = 0;
	neg = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count + neg + 1);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	size;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	size = lengthcalcul(n);
	result = (char *)malloc(size * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (n == 0)
		result[0] = '0';
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	result[size - 1] = '\0';
	while (n > 0)
	{
		size--;
		result[size - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}

//#include <limits.h>
/* 
static size_t	ft_size(int n)
{
	size_t	len;
	int		sig;

	len = 0;
	sig = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		sig = 1;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len + 1 + sig);
}

static char	*ft_reverse(char *str1)
{
	char	*reverse;
	size_t	i;
	size_t	len;		

	i = 0;
	len = 0;
	while (str1[len])
		len++;
	reverse = (char *)malloc((len + 1) * sizeof(char));
	if (reverse == NULL)
		return (NULL);
	while (i < len)
	{
		reverse[i] = str1[len - i - 1];
		i++;
	}
	reverse[len] = '\0';
	return (reverse);
}

static char	*ft_itoa_abs(int n, char *string1, int neg)
{
	size_t	i;

	i = 0;
	while (n != 0)
	{
		string1[i++] = n % 10 + '0';
		n /= 10;
	}
	if (neg == 1)
		string1[i++] = '-';
	string1[i] = '\0';
	return (string1);
}

char	*ft_itoa(int n)
{
	char	*string1;
	char	*result;
	int		neg;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	neg = 0;
	string1 = (char *)malloc(ft_size(n) * sizeof(char));
	if (string1 == NULL)
		return (NULL);
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	result = ft_reverse(ft_itoa_abs(n, string1, neg));
	free(string1);
	return (result);
}
 */