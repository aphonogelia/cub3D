/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:14:51 by htharrau          #+#    #+#             */
/*   Updated: 2025/03/21 18:04:10 by htharrau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF
# define YELLOW 0xFFFF00FF
# define CYAN 0x00FFFFFF
# define MAGENTA 0xFF00FFFF
# define GRAY 0x808080FF
# define ORANGE 0xFFA500FF
# define PURPLE 0x800080FF
# define BROWN 0xA52A2AFF
# define PINK 0xFFC0CBFF
# define LIME 0x00FF00FF
# define TEAL 0x008080FF
# define NAVY 0x000080FF

# define M_PI 3.14159265358979323846
# define MAX_DIST 1e5

# define WIDTH 800
# define HEIGHT 600

# define OFFSET 10
# define TILE_SIZE 4
# define MVT_SPEED 0.07
# define ROT_SPEED 0.055

# define FOV 66
# define WALL_SIZE 2
# define MOUSE_SENS 0.01       // mouse sensitivity
# define INTERACTION_RANGE 8.0f // interaction from doors
# define MAX_DOORS 25
# define PLAYER_SPACE 0.35



// map items
# define WALL '1'
# define DOOR '2'

// Minimap colors
# define PLY_COL MAGENTA
# define TILE_COL BROWN
# define FLOOR_COL PINK
# define DOOR_COL PURPLE
# define BACK_COL NAVY
# define RAY_COL LIME

// status states
# define PARSE_ERR 3
# define MALLOC_ERR 2
# define FAILURE 1
# define SUCCESS 0

# define MAX_TEXTURES 5

// Walls
# define NORTH 0
# define WEST 1
# define SOUTH 2
# define EAST 3

# define DOOR_TEXTURE 4

// Wall default colors
# define CLR_NORTH TEAL
# define CLR_WEST ORANGE
# define CLR_SOUTH PURPLE
# define CLR_EAST GRAY
# define CLR_DOOR BROWN

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <linux/input-event-codes.h>
# include <math.h>
# include <time.h>

typedef struct s_input
{
	char			**map;
	int				w_map;
	int				h_map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				floor;
	int				sky;
	int				play_x;
	int				play_y;
	char			player_dir;
	int				doors_nbr;
}					t_input;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle_r;
}					t_player;

typedef struct s_door
{
	float			x;
	float			y;
	int				open;
	int				exit_game;
}					t_door;

typedef struct s_screen
{
	mlx_texture_t	*tex;
	mlx_image_t		*welcome_img;
	int32_t			orig_w;
	int32_t			orig_h;
	mlx_image_t		*background;
	bool			is_welcome;
}					t_screen;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_input			input;
	t_player		player;
	t_screen		screen;
	t_door			doors[MAX_DOORS];
	mlx_texture_t	**textures;
	bool			flag_refresh;

}					t_data;

typedef struct s_ray
{
	float			curr_angle;
	float			curr_arctan;
	float			cos_angle;
	float			sin_angle;
	float			cos_angle_diff;
	int				map_x;
	int				map_y;
	float			dist_x;
	float			dist_y;
	float			hypo_x;
	float			hypo_y;
	int				step_x;
	int				step_y;
	float			distance;
	float			corr_dist;
	int				line_length;
	int				wall_orient;
	float			wall_x;
	float			hit_x;
	float			hit_y;
}					t_ray;

typedef struct s_texture
{
	mlx_texture_t	*png;
	int				tex_x;
	int				tex_y;
	uint32_t		color;
	int				text_top;
	float			text_pos;
}					t_texture;

typedef struct s_coord
{
	float			x;
	float			y;
}					t_coord;

typedef struct s_mvt
{
	int				key;
	float			delta_x;
	float			delta_y;
}					t_mvt;

/******************************************************************************/
/******************************************************************************/
/*								PARSING											*/
/******************************************************************************/
/******************************************************************************/

int					parser(char *file_name, t_data *data);
int					parse_elements(char *line, t_data *data, int found_map);
void				init_data(t_data *data);
int					save_map(int fd, t_data *data, char **line, int *found_map);
int					trim_lines(t_data *data);
int					trim_rightend(t_data *data);
int					trim_leftend(t_data *data);
int					valid_chars(t_data *data, int i, int j);
int					valid_map(t_data *data, int status);
int					ft_isspace(char c);
void				free_2d_char(char **arr);
int					line_empty(char *line);
char				*valid_first_occurance(char *str);
void				clean_parse(t_data *data);

/******************************************************************************/
/******************************************************************************/
/*								RAYCASTING										*/
/******************************************************************************/
/******************************************************************************/

// HELENE
void				init_mlx(t_data *data);
void				hoop_func(void *param);
void				update_fov(t_data *data);
bool				close_wall(t_data *data, float x, float y);
void				draw_ceiling_floor(t_data *data);
void				draw_walls(t_data *data);
void				cast_rays(t_data *data, t_ray *ray);
bool				wall_check(t_data *data, t_ray *ray);
void				draw_miniray(t_data *data, t_ray *ray);
void				draw_minimap(t_data *data);
void				escape_handle(mlx_key_data_t keys, void *param);
float				deg_to_rad(int nb);
float				deg_to_rad(int nb);
void				resize_hook(int32_t width, int32_t height, void *param);
void				handle_error(char *error_message, t_data *data);
void				handle_error2(char *error_message, t_data *data,
						int exit_status);
void				close_window(void *param);
void				close_window2(void *param, int exit_status);
// float	rad_to_degree(float nb);

/******************************************************************************/
/******************************************************************************/
/*									TEXTURES									*/
/******************************************************************************/
/******************************************************************************/

void				load_textures(t_data *data);
uint32_t			sample_color(t_texture *texture);
int					calc_texture_x(t_ray *ray, mlx_texture_t *texture);
int					use_default_clr(int wall_orient);
void				clean_textures(t_data *data);

/******************************************************************************/
/******************************************************************************/
/*									OTHER										*/
/******************************************************************************/
/******************************************************************************/

void				welcome_screen(t_data *data);
void				print_player(t_player *player);
void				print_input(t_data *data);
void				print_data(t_data *data);
int					err_msg(char *msg, int err_nr);
void				print_ray1(t_ray *ray);
void				print_ray2(t_ray *ray);
void				exit_err(t_data *data, char *msg, int exit_status);

// BONUS
void				mouse_callback(double xpos, double ypos, void *param);
void				init_doors(t_data *data);
void				doors_interaction(t_player *player, t_door *doors,
						int doors_nbr);

#endif
