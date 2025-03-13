/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:35:22 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* char **ft_split(char const *s, char c);
Parameters s: The string to be split. c: The delimiter character.
Return value The array of new strings resulting from the split.
NULL if the allocation fails.
External functs. malloc, free
Description Allocates (with malloc(3)) and returns an array of strings obtained 
by splitting ’s’ using the character ’c’ as a delimiter. The array must end
with a NULL pointer. */

#include "libft.h"

static int	ft_nbarray(const char *s, char c)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**create_matrix(int count)
{
	char	**matrix;

	matrix = (char **)malloc((count + 1) * sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	return (matrix);
}

static char	**sub_matrix(char **matrix, char const *s, char c, int count)
{
	int		j;
	size_t	substring;

	j = 0;
	while (j < count && *s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		substring = 0;
		while (s[substring] != '\0' && s[substring] != c)
			substring++;
		matrix[j] = (char *)malloc((substring + 1) * sizeof(char));
		if (matrix[j] == NULL)
		{
			while (j >= 0)
				free(matrix[j--]);
			free(matrix);
			return (NULL);
		}
		j++;
		s += substring;
	}
	return (matrix);
}

static char	**fill_matrix(char **matrix, char const *s, char c, int count)
{
	int		j;
	size_t	k;
	size_t	substring;

	j = 0;
	while (j < count && *s != '\0')
	{
		while (*s == c)
			s++;
		substring = 0;
		while (s[substring] != '\0' && s[substring] != c)
			substring++;
		k = 0;
		while (k < substring)
		{
			matrix[j][k] = s[k];
			k++;
		}
		matrix[j][k] = '\0';
		j++;
		s += substring;
	}
	matrix[j] = NULL;
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		count;

	if (!s)
		return (NULL);
	count = ft_nbarray(s, c);
	matrix = create_matrix(count);
	if (matrix == NULL)
		return (NULL);
	matrix = sub_matrix(matrix, s, c, count);
	if (matrix == NULL)
		return (NULL);
	matrix = fill_matrix(matrix, s, c, count);
	return (matrix);
}

/* int	main(void)
{
	char	*s = "bbbbbbbbb";
 	char	**result = ft_split(s, 'b');
	size_t	i = 0;

	while (result[i])
	{
		printf("%s\n",  result[i]);
		i++;
	}
	return (0);
}  */
