/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:07:02 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* copy one string to another but it always NUL-terminate the string.
If you give a dstsize long enough to NUL-terminate the string without trunca-
ting it, strlcpy() will simply copy the string, as you'd do with strcpy(). If
you don't give a dstsize long enough, it will copy dstsize - 1 characters from
the source into the destination, adding the NUL-terminating character after that
The strlcpy() function always returns the length of the string that it tried to
create, this is the length of src, even if you have to truncate the string to 
NUL-terminate it.
RETURN VALUES
The strlcpy() and strlcat() functions return the total length of the string they 
tried to create.  For strlcpy() that means the length of src.  
For strlcat() that means the initial length of dst plus the length of src. While 
this may seem somewhat confusing, it was done to make truncation detection
simple */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (!src || !dst || size == 0)
		return (srclen);
	while (src[i] && size > 1 && (i < (size - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}
