/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/14 14:31:59 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// Convert texture to a displayable image and put on screen
void    welcome_screen(t_data *data)
{
    mlx_texture_t* texture = mlx_load_png("imgs/fab.png");
    mlx_image_t* img = mlx_texture_to_image(data->mlx, texture);
    if (!img)
        exit_err(data, "Welcome screen", FAILURE);

    if (mlx_image_to_window(data->mlx, img, 0, 0) < 0)
        exit_err(data, "Welcome screen", FAILURE);
}