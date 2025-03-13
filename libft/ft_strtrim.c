/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:35:03 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  s1: The string to be trimmed, set: The reference set of characters to trim.
Return value The trimmed string. NULL if the allocation fails.
Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters spe-
cified in ’set’ removed from the beginning and the end of the string.*/

#include "libft.h"

static char	*allocation(int len)
{
	char	*new;

	new = (char *)malloc((len + 1) * (sizeof(char)));
	if (new == NULL)
		return (NULL);
	new[0] = '\0';
	return (new);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = ft_strlen(s1);
	k = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (i == ft_strlen(s1))
		return (allocation(0));
	while ((j - 1 > i) && ft_strchr(set, s1[j - 1]))
		j--;
	new = allocation(j - i);
	if (new == NULL)
		return (NULL);
	while (k < j - i)
	{
		new[k] = s1[k + i];
		k++;
	}
	new[k] = '\0';
	return (new);
}

/* int	main(void)
{
	const char	*snetene = "12lsdfe12457dl4f2s5  '";
	const char	*set = " ./123456789'";
	char		*new;

	new = ft_strtrim(snetene, set);
	printf("%s\n", new);
	free(new);
	return (0);
} */
