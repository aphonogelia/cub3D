/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbar <inbar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/15 14:53:59 by inbar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void           welcome_screen(t_data *data);

    void init_welcome_screen(t_data *data)
{
    mlx_texture_t* tex = mlx_load_png("imgs/fab.png");
    if (!tex)
        exit_err(data, "Failed to load welcome texture", FAILURE);

    // Create background image (black)
    data->screen.background = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
    
    // Manually fill background with black pixels
    for (int y = 0; y < data->mlx->height; y++)
        for (int x = 0; x < data->mlx->width; x++)
            mlx_put_pixel(data->screen.background, x, y, 0x000000FF);

    // Create welcome image with original texture dimensions
    data->screen.welcome_img = mlx_texture_to_image(data->mlx, tex);
    
    // Center positioning
    int pos_x = (data->mlx->width - tex->width) / 2;
    int pos_y = (data->mlx->height - tex->height) / 2;
    
    // Display images
    mlx_image_to_window(data->mlx, data->screen.background, 0, 0);
    mlx_image_to_window(data->mlx, data->screen.welcome_img, pos_x, pos_y);
    
    data->screen.is_welcome = true;
    mlx_delete_texture(tex);
}

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