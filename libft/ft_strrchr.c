/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:07:14 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strrchr() function returns a pointer to the last occurrence of  the
character c in the string s.
The strchr() and strrchr() functions return a pointer  to  the  matched
character  or NULL if the character is not found.  The terminating null byte is
considered part of the string, so that if  c  is  specified  as '\0', these 
functions return a pointer to the terminator.
Since the function's return type (char *) does not match the type of the expre
ssion being returned (const char *), a typecast is needed to inform the compiler
to treat the return value as a non-constant pointer to a character (char *). */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)(s + i));
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

/* int	main(void)
{
	char *mystring = "la nature est belle";
	int c = 'e';

	printf("%s\n", ft_strrchr(mystring, c));
	printf("%s\n", strrchr(mystring, c));
	printf("my ft_strrchr: %p\n", ft_strrchr(mystring, '\0'));
	printf("built in strrchr: %p\n", strrchr(mystring, '\0'));
	return (0);
} */
