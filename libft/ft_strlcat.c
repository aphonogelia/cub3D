/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:58 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	j = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	if (dstlen >= size)
		return (srclen + size);
	while (dst[j] && j < size - 1)
		j++;
	while (src[i] && (j + i < size - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j + i < size)
		dst[j + i] = '\0';
	return (dstlen + srclen);
}

/*int	main(void)
{
	char			*source = "AAAAAAAAA";
	char			destination[30] = "B";
	unsigned int	taille = 5;

	printf("size is %u, dest length is %lu\n", taille, 
		ft_strlcat(destination, source, taille));
	printf("%s", destination);
	return (0);
} 

	char dest[30]; 
	memset(dest, 0, 30);
	char *src = "AAAAAAAAA";
	dest[0] = 'B';
	ft_strlcat(dest, src, 0)
	strlen(src)
	!strcmp(dest, "B")*/