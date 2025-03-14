/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/14 16:15:33 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// // Convert texture to a displayable image and put on screen
// void    welcome_screen(t_data *data)
// {
//     mlx_texture_t* texture = mlx_load_png("imgs/fab.png");
//     mlx_image_t* img = mlx_texture_to_image(data->mlx, texture);
//     if (!img)
//         exit_err(data, "Welcome screen", FAILURE);

//     if (mlx_image_to_window(data->mlx, img, 0, 0) < 0)
//         exit_err(data, "Welcome screen", FAILURE);
// }


void welcome_screen(t_data *data)
{
    mlx_texture_t* texture = mlx_load_png("imgs/fab.png");
    if (!texture)
        exit_err(data, "Failed to load texture", FAILURE);

    int32_t width = data->mlx->width;
    int32_t height = data->mlx->height;

    mlx_image_t* img = mlx_new_image(data->mlx, width, height);
    if (!img)
        exit_err(data, "Failed to create image", FAILURE);

    uint8_t* pixels = img->pixels;
    int32_t y = 0;
    while (y < height)
    {
        int32_t x = 0;
        while (x < width)
        {
            uint32_t tex_x = (x * texture->width) / width;
            uint32_t tex_y = (y * texture->height) / height;
            uint32_t color = *((uint32_t*)texture->pixels + tex_y * texture->width + tex_x);
            *((uint32_t*)pixels + y * width + x) = color;
            x++;
        }
        y++;
    }

    if (mlx_image_to_window(data->mlx, img, 0, 0) < 0)
        exit_err(data, "Failed to put image to window", FAILURE);

    mlx_delete_texture(texture);
}