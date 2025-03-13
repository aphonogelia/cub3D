/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:27:04 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/04 10:08:16 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function iterates through each node in a linked list and applies a gi-
ven function ('f') to the content of each node. It takes the address of the 
first link of the list ('lst') and a function pointer ('f') as parameters. The
'f' function is applied to the content of each node in the list.*/

#include "libft.h"

/* typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list; */

/* void	print_content(void *content)
{
	int	*num;

	num = (int *)content;
	printf("%d ", *num);
} */

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f || !lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* int	main(void)
{
	t_list	*head;
	t_list	*temp; 

	head = malloc(sizeof(t_list));
	head->content = malloc(sizeof(int));
	head->next = malloc(sizeof(t_list));
	*((int *)(head->content)) = 1;
	head->next->content = malloc(sizeof(int));
	*((int *)(head->next->content)) = 2;
	head->next->next = NULL;
	printf("Linked list content: ");
	ft_lstiter(head, &print_content);
	printf("\n");
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
	return (0);
}*/
