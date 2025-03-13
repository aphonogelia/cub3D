/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:53 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strchr() function returns a pointer to the first occurrence of the
character c in the string s.
The strchr() and strrchr() functions return a pointer  to  the  matched
character  or NULL if the character is not found. The terminating null byte is
considered part of the string, so that if  c  is  specified  as '\0', these 
functions return a pointer to the terminator.
Since the function's return type (char *) does not match the type of the expre
ssion being returned (const char *), a typecast is needed to inform the compiler
to treat the return value as a non-constant pointer to a character (char *). */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

/* int	main(void)
{
	char	*mystring = "teste";
	int		c = '\0';

	printf("string ft_strchr %s\n", ft_strchr(mystring, c));
	printf("string in strchr %s\n", strchr(mystring, c));
	printf("addresse depart: %p\n", mystring);
	printf("my ft_strchr: %p\n", ft_strchr(mystring, '\0'));
	printf("built in strchr: %p", strchr(mystring, '\0'));
	return (0);
} */
