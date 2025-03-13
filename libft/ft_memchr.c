/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:38 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* void *memchr() searches for the first occurrence of the character c in the 
first n bytes of the string pointed to, by the argument str. Both c and the 
bytes of the memory area pointed to by s are interpreted as unsigned char. 
memchr searches for the occurrence of a specific byte value within a block of 
memory. It treats the input as a block of memory, not necessarily null-termina-
ted strings. It searches for a specific byte value within a block of memory, 
regardless of whether it represents characters or other data types. It returns 
a pointer to the first occurrence of the byte value within the specified memory 
block or NULL if the byte value is not found. */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((const unsigned char *)s + i) == (unsigned char)c)
			return ((void *)(const unsigned char *)s + i);
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	char	*string = "la nature est un temple";
	int		array[] = {5, 12, 36, 54};
	int 	a = 't';
	int		n = 15;

	printf("%c\n", *(char *)ft_memchr(string, a, n));
	printf("%p", (char *)ft_memchr(string, a, n));
} */
