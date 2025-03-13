/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:13 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*array;
	size_t			totalsize;

	if (nmemb == 0 || size == 0)
		totalsize = 0;
	else if (nmemb > __SIZE_MAX__ / size)
		return (NULL);
	else
		totalsize = nmemb * size;
	array = (unsigned char *)malloc(totalsize * sizeof(char));
	if (array == NULL)
		return (NULL);
	ft_memset((void *)array, 0, totalsize);
	return ((void *)(array));
}

/*int	main(void)
{
	char	*mystring;
	int		*myarray;

	mystring = ft_calloc(SIZE_MAX, SIZE_MAX);
	return (0);
} 

#include "sigsegv.hpp"
#include "check.hpp"
#include "leaks.hpp"
#include <string.h>
#include <limits.h>

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv);
	title("ft_calloc\t: ")

	void * p = ft_calloc(2, 2);
	char e[] = {0, 0, 0, 0};

	check(ft_calloc(SIZE_MAX, SIZE_MAX) == NULL); showLeaks();
	p = ft_calloc(0, -5);
	write(1, "\n", 1);
	return (0);
}*/