/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:14:14 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/21 16:51:43 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

int	err_msg(char *msg, int exit_status)
{
	printf("Error\n%s\n", msg);
	return (exit_status);
}

void	exit_err(t_data *data, char *msg, int exit_status)
{
	err_msg(msg, 0);
	clean_parse((data));
	ft_printf("Exiting program...\n");
	exit(exit_status);
}
