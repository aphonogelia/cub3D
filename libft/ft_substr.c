/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:34:12 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Parameters s: The string from which to create the substring. start: The start
index of the substring in the string ’s’. len: The maximum length of the sub-
string. Return value The substring. NULL if the allocation fails.
Allocates (with malloc(3)) and returns a substring from the string
’s’. The substring begins at index ’start’ and is of maximum size ’len’*/

#include "libft.h"

static char	*allocation(size_t len)
{
	char	*newstring;

	newstring = (char *)malloc((len + 1) * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	newstring[0] = '\0';
	return (newstring);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*newstring;
	unsigned int	i;
	size_t			slength;

	if (s == NULL)
		return (NULL);
	slength = ft_strlen(s);
	i = 0;
	if (start > slength)
		return (allocation(0));
	if (len > slength - start)
		len = slength - start;
	newstring = allocation(len);
	if (newstring == NULL)
		return (NULL);
	while (i < len && s[i + start])
	{
		newstring[i] = s[i + start];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
/* 
int	main(void)
{
	char const		*s = "tripouille";
	unsigned int	start = 0;
	size_t			len = 42000;
	char const 		*test;
	int				i = 0;

	test = ft_substr(s, start, len);
	while (test[i])
		i++;
	printf("%d",i);
	printf("%s", ft_substr(s, start, len));
	return (0);
} */
