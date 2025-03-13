/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:50 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The memset() function fills the first n bytes of the memory area pointed to 
by s with the constant byte c. The memset() function returns a pointer to the 
memory area s.*/

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return ((void *)s);
}
/* 
int	main(void)
{
	char	string[20]; 
	char	string1[20]; 
	size_t	i = 0;

	ft_memset(string, 'h', 21);
	while (i < 21)
		printf("%c ", string[i++]);
	printf("\n");
	memset(string1, 'h', 21);
	while (i < 21)
		printf("%c ", string1[i++]);
	printf("\n");
	return (0);
} */
