/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:47:34 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/22 17:49:01 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d.h"

void	handle_error(char *error_message, t_data *data);
void	handle_error2(char *error_message, t_data *data, int exit_status);
void	close_window(void *param);
void	close_window2(void *param, int exit_status);

void	handle_error(char *error_message, t_data *data)
{
	ft_printf("Error: %s\n", error_message);
	close_window(data);
}

void	handle_error2(char *error_message, t_data *data, int exit_status)
{
	ft_printf("Error: %s\n", error_message);
	close_window2(data, exit_status);
}

void	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_parse(data);
	ft_printf("Exiting program...\n");
	exit(1);
}


void	close_window2(void *param, int exit_status)
{
	t_data	*data;

	data = (t_data *)param;
	clean_parse(data);
	ft_printf("Exiting program...\n");
	exit(exit_status);
}
