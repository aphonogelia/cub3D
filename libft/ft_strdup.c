/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:55 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strdup() function returns a pointer to a new string which is a duplicate 
of the string s.  Memory for the new  string  is  obtained with malloc(3), and 
can be freed with free(3). On success, the strdup() function returns a pointer 
to the duplicated  string. It returns NULL if insufficient memory was available, 
with errno set to indicate the cause of the error.*/

#include "libft.h"

char	*ft_strdup(char *src)
{
	char		*string;
	size_t		i;
	size_t		length;

	i = 0;
	length = 0;
	while (src[length])
		++length;
	string = (char *)malloc(sizeof(char) * (length + 1));
	if (string == NULL)
		return (NULL);
	while (src[i])
	{
		string[i] = src[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

/* int	main(void)
{
	char	*str1 = "la nature est un temple";
	char	*str2 ;

	str2 = ft_strdup(str1);
	printf("%s addresse str1 %p\n", str1, str1);
	printf("%s addresse str2 %p\n", str2, str2);
	return (0);
} */
