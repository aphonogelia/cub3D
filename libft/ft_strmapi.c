/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:36:23 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* s: The string on which to iterate. f:  function to apply to each character.
Return value The string created from the successive applications of ’f’.
Returns NULL if the allocation fails.
Applies the function f to each character of the string s, passing its index as 
the first argument and the character itself as the second. A new string is crea-
ted (using malloc) to collect the results from the successive applications .*/

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*newstring;

	i = 0;
	if (!s)
		return (NULL);
	newstring = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	while (s[i])
	{
		newstring[i] = f(i, s[i]);
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}

char	modify(unsigned int index, char c)
{
	return (c + index);
}

/* int	main(void)
{
	char	str[] = "Le_grand_schlem";
	char	*new = ft_strmapi(str, modify);

	printf("%s\n", str);
	printf("%s\n", new);
	free(new);
	return (0);
} */
