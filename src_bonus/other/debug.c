/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:25:58 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/26 11:55:33 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc_bonus/cub3d_bonus.h"



void	print_player(t_player *player)
{
	printf("\n=== PLAYER INFO ===\n");
	printf("Position: (%.2f, %.2f)\n", player->x, player->y);
	printf("Angle radian: %.2f\n", player->angle_r);
}

void	print_input(t_data *data)
{
	int		i;
	t_input	input;

	input = data->input;
	printf("\n=== INPUT INFO ===\n");
	printf("Map Dimensions: %d x %d\n", input.w_map, input.h_map);
	printf("Textures:\n");
	printf("  North: %s\n", input.no);
	printf("  South: %s\n", input.so);
	printf("  West: %s\n", input.we);
	printf("  East: %s\n", input.ea);
	printf("Colors:\n");
	printf("  Floor: %#x\n", input.floor);
	printf("  Ceiling: %#x\n", input.sky);
	printf("Player:\n");
	printf("  (x, y): (%d, %d)\n", input.play_x, input.play_y);
	printf("  Facing: %c\n", input.player_dir);
	printf("\nMap:\n");
	i = 0;
	while (i < input.h_map)
	{
		printf("%s$\n", input.map[i]);
		i++;
	}
	print_doors(data);
}

void	print_data(t_data *data)
{
	printf("\n=== GAME DATA ===\n");
	printf("Window dimensions: %d x %d\n", data->mlx->width, data->mlx->height);
	print_input(data);
	print_player(&data->player);
}

void	print_doors(t_data *data)
{
	int	i;

	i = 0;
	printf("\n=== DOORS ===\n");
	while (i <= data->input.doors_nbr)
	{
		printf("Door ( %f, %f )", data->doors[i].x, data->doors[i].y);
		if (data->doors[i].open)
			printf(" open");
		else
			printf(" closed");
		if (data->doors[i].exit_game)
			printf(" Exit door\n");
		else
			printf("\n");
		i++;
	}
}
