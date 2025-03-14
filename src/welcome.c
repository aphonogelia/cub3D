/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:13:05 by ilazar            #+#    #+#             */
/*   Updated: 2025/03/14 17:33:11 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void           welcome_screen(t_data *data);
static void    draw_on_screen(t_data *data, mlx_texture_t* texture, \
    int32_t height, int32_t width);

void welcome_screen(t_data *data)
{
    mlx_texture_t* texture;
    int32_t        width;
    int32_t        height;
    
    texture = mlx_load_png("imgs/fab.png");
    if (!texture)
        exit_err(data, "Failed to load welcome screen", FAILURE);
    width = data->mlx->width;
    height = data->mlx->height;
    data->screen.welcome_img = mlx_new_image(data->mlx, width, height);
    if (!data->screen.welcome_img)
        exit_err(data, "Failed to create welcome screen", FAILURE);
    draw_on_screen(data, texture, height, width);
    
        data->screen.is_welcome = true;
    mlx_delete_texture(texture);
}

static void    draw_on_screen(t_data *data, mlx_texture_t* texture, \
    int32_t height, int32_t width)
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
            tex_x = (x * texture->width) / width;
            tex_y = (y * texture->height) / height;
            *((uint32_t*)pixels + y * width + x) =  \
            *((uint32_t*)texture->pixels + tex_y * texture->width + tex_x);
            x++;
        }
        y++;
    }
    if (mlx_image_to_window(data->mlx, data->screen.welcome_img, 0, 0) < 0)
        exit_err(data, "Failed to put image to window", FAILURE);
}
