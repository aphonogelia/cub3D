/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:27:14 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function calculates the number of nodes in a linked list. It takes the
beginning of the list ('lst') as a parameter and iterates through the list, 
counting each node until reaching the end. It returns the total count of nodes
in the list.*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		n;
	t_list	*x;

	n = 0;
	if (!lst)
		return (0);
	x = lst;
	while (x)
	{
		x = x->next;
		n++;
	}
	return (n);
}
