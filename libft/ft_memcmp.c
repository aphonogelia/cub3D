/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:41 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The memcmp() function compares the first n bytes (each interpreted as un -
signed char) of the memory areas s1 and s2. The memcmp() function returns an 
integer less than, equal to, or greater than zero if the first n bytes of s1 
is found, respectively, to be less than, to match, or be greater than the first
n bytes of s2. For a nonzero return value, the sign is determined by the sign
of the difference between the first pair of bytes (interpreted as unsigned char)
that differ in s1 and s2. If n is zero, the return value is zero.*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/* int	main(void)
{
	char	str1[] = "12345";
	char	str2[] = "12348";

	printf("result: %d\n", ft_memcmp(str1, str2, 5)); 
	return (0);
} */
