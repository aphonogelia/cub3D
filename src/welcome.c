/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/14 20:19:52 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void           welcome_screen(t_data *data);

void welcome_screen(t_data *data)
{
    int32_t        width;
    int32_t        height;
    
    data->screen.texture = mlx_load_png("imgs/fab.png");
    if (!data->screen.texture)
        exit_err(data, "Failed to load welcome screen", FAILURE);
    width = data->mlx->width;
    height = data->mlx->height;
    data->screen.welcome_img = mlx_new_image(data->mlx, width, height);
    if (!data->screen.welcome_img)
        exit_err(data, "Failed to create welcome screen", FAILURE);
    draw_on_screen(data, height, width);
    
    data->screen.is_welcome = true;
    mlx_delete_texture(data->screen.texture);
}

void    draw_on_screen(t_data *data, int32_t height, int32_t width)
{
    uint8_t *pixels;
    uint32_t tex_x;
    uint32_t tex_y;
    int32_t  y;
    int32_t  x;
    
    pixels = data->screen.welcome_img->pixels;
    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            tex_x = (x * data->screen.texture->width) / width;
            tex_y = (y * data->screen.texture->height) / height;
            *((uint32_t*)pixels + y * width + x) =  \
            *((uint32_t*)data->screen.texture->pixels + tex_y * data->screen.texture->width + tex_x);
            x++;
        }
        y++;
    }
    if (mlx_image_to_window(data->mlx, data->screen.welcome_img, 0, 0) < 0)
        exit_err(data, "Failed to put image to window", FAILURE);
}