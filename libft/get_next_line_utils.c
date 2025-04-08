/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:19:59 by htharrau          #+#    #+#             */
/*   Updated: 2025/02/19 15:37:47 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cleanup_stash(char	*stash[]);

// Cleanup all stashes when called with invalid fd
void	cleanup_stash(char	*stash[])
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		if (stash[i])
		{
			free(stash[i]);
			stash[i] = NULL;
		}
		i++;
	}
}