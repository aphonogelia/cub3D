/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:07:11 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* CONSTANT CHAR? SIZE_T? */
/* The strnstr() function locates the first occurrence of the null-terminated 
string little in the string big, where not more than len characters are searched.
Characters that appear after a ‘\0’ character are not searched. If little is an 
empty string, big is returned; if little occurs nowhere in big, NULL is returned;
otherwise a pointer to the first character of the first occurrence of little is 
returned. */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (little[i] && big[j] && j < len)
	{
		if (little[i] == big[j])
		{
			if (little[i + 1] == '\0')
				return ((char *)big + j - i);
			i++;
			j++;
		}
		else
		{
			j = j - i + 1;
			i = 0;
		}
	}
	return (0);
}

/* int	main(void)
{
	char	str[] = "abcd01abcd012et";
	char	to_find[] = "12";
	char	*result;

	printf("Substring is : %s \n
    Found at index : %s\n", to_find, ft_strnstr(str, to_find, 10));
	return (0);
}
 */