/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:06:08 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  The bzero function erases the data in the n bytes of the memory starting at 
the location pointed to by s, by writing zeros (bytes containing '\0') to that 
area.
The  explicit_bzero()  function  addresses  a problem that security-conscious ap
lications may run into when using bzero(): if the compiler can deduce that the
location to zeroed will never again be touched by a correct program, then it may
remove the bzero() call altogether.  This is a problem if the intent of the
bzero() call was to erase sensitive data (e.g., passwords) to prevent the possi‐
bility that the data was leaked by an incorrect or compromised program. */

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

/*int main (void)
{
	char	mystring[4] = "ferg";
	int		myarray[5] = {12, 5, 34, -8, 56};
	int		i = 0;

	printf("Before ft_bzero on mystring: \"%s\"\n", mystring);
	ft_bzero(mystring, 5 * sizeof(char));
	printf("After ft_bzero on mystring: \"%s\"\n", mystring);
	printf("Before ft_bzero on myarray: ");
	while (i < 5)
	{
		printf("%d ", myarray[i]);
		i++;
	}	
	printf("\n");
	ft_bzero(myarray, 5 * sizeof(int));
	printf("After ft_bzero on myarray: ");
	i = 0;
	while (i < 5)
	{
		printf("%d ", myarray[i]);
		i++;
	}	
	printf("\n");
	return (0);
}*/
