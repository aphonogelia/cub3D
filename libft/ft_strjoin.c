/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:34:42 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* s1: The prefix string. s2: The suffix string. Return value The new string.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns a new string, which is the result of the
concatenation of ’s1’ and ’s2’.*/

#include "libft.h"

char	*ft_strjoin(char const *s1, const char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

/* int	main(void)
{
	char	*s1 = "bateau";
	char	*s2 = "grenier";

	printf("string1 %s\n", s1);
	printf("string2 %s\n", s2);
	printf("newstring %s\n", ft_strjoin(s1, s2));
	return (0);
} */
