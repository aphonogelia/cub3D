/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:14:51 by htharrau          #+#    #+#             */
/*   Updated: 2025/04/10 07:58:46 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# define LAVENDER 0xE6E6FAFF
# define PEACH 0xFFDAB9FF
# define MINT 0x98FF98FF
# define CORAL 0xFF7F50FF
# define TURQUOISE 0x40E0D0FF
# define SALMON 0xFA8072FF
# define PERIWINKLE 0xCCCCFFFF
# define MAUVE 0xE0B0FFFF
# define SAGE 0xBCECACFF
# define LILAC 0xC8A2C8FF
# define APRICOT 0xFFB347FF
# define SKY_BLUE 0x87CEEBFF
# define BLUSH 0xFFB6C1FF
# define SEAFOAM 0x98FB98FF
# define ROSE 0xFFB3BAFF
# define LEMON 0xFFFACD8F
# define COLUMBIA_BLUE 0xC8D9F0FF
# define BLUSH_TRANSLUCENT 0xFFB6C180 // Approximately 50% translucent

// Minimap
# define PLAYER_COL CORAL
# define TILE_COL ROSE
# define DOOR_COL ROSE
# define RAY_COL MAGENTA
# define OFFSET 5
# define TILE_SIZE 7
# define PLAYER_X 200
# define PLAYER_Y 80
# define PLAYER_SPACE 0.25

# define FLOOR_COL LEMON
# define BACK_COL NAVY

// Wall floor sky default colors
# define CLR_SKY COLUMBIA_BLUE
# define CLR_FLOOR LEMON
# define CLR_NORTH MINT
# define CLR_WEST SAGE
# define CLR_SOUTH LILAC
# define CLR_EAST APRICOT
# define CLR_DOOR BROWN

# define M_PI 3.14159265358979323846
# define MAX_DIST 1e5

# define WIDTH 1000
# define HEIGHT 1000

// menus
# define WELCOME_SCREEN "imgs/cube.png"
# define END_SCREEN "imgs/cube_end.png"
# define DR_TEX_PATH "imgs/door1.png"

# define FOV 66
# define MVT_SPEED 0.07
# define ROT_SPEED 0.045
# define MAX_DOORS 15

// map items
# define WALL '1'
# define DOOR '2'

// status states
# define PARSE_ERR 3
# define MALLOC_ERR 2
# define FAILURE 1
# define SUCCESS 0

# define MAX_TEXTURES 5

// Walls orient
# define NO_ORIENT -1
# define NORTH 0
# define WEST 1
# define SOUTH 2
# define EAST 3
# define DOOR_TEXTURE 4

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
	float			x_offset;
	float			y_offset;
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

typedef struct s_miniray
{
	float			cos_angle;
	float			sin_angle;
	float			distance;
}					t_miniray;

typedef struct s_mouse
{
	double			last_x;
	double			cursor_last_moved;
	bool			first_call;
}					t_mouse;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_input			input;
	t_player		player;
	t_screen		screen;
	t_mouse			mouse;
	t_door			doors[MAX_DOORS];
	mlx_texture_t	**textures;
	bool			flag_refresh;
	t_miniray		*miniray;

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
/*								PARSING										*/
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
int					valid_map(t_data *data, int status, int i);
int					is_wall(t_data *data, int row, int col);
int					ft_isspace(char c);
void				free_2d_char(char **arr);
int					line_empty(char *line);
char				*valid_first_occurance(char *str);
void				clean_parse(t_data *data);

/******************************************************************************/
/******************************************************************************/
/*								RAYCASTING									*/
/******************************************************************************/
/******************************************************************************/

void				init_mlx(t_data *data);
void				init_player(t_data *data);
void				hoop_func(void *param);
void				update_fov(t_data *data);
bool				close_wall(t_data *data, float x, float y);
void				draw_ceiling_floor(t_data *data);
int					draw_walls(t_data *data);
void				cast_rays(t_data *data, t_ray *ray);
void				wall_orient(t_data *data, t_ray *ray);
bool				wall_check(t_data *data, t_ray *ray);
void				draw_miniray(t_data *data, int u);
void				save_miniray(t_data *data, t_ray *ray, int u);
void				draw_minimap(t_data *data);
void				keys_handle(mlx_key_data_t keys, void *param);
float				deg_to_rad(int nb);
float				rad_to_deg(float nb);
void				put_pixel_minimap(t_data *data, int x, int y,
						uint32_t color);
void				resize_hook(int32_t width, int32_t height, void *param);
void				handle_error(char *error_message, t_data *data);

/******************************************************************************/
/******************************************************************************/
/*									TEXTURES								*/
/******************************************************************************/
/******************************************************************************/

void				load_textures(t_data *data);
uint32_t			sample_color(t_texture *texture);
int					calc_texture_x(t_ray *ray, mlx_texture_t *texture);
int					use_default_clr(int wall_orient);
void				clean_textures(t_data *data);

/******************************************************************************/
/******************************************************************************/
/*									OTHER									*/
/******************************************************************************/
/******************************************************************************/

void				print_player(t_player *player);
void				print_input(t_data *data);
void				print_doors(t_data *data);
void				print_data(t_data *data);
int					err_msg(char *msg, int err_nr);
void				print_ray1(t_ray *ray);
void				print_ray2(t_ray *ray);
void				exit_err(t_data *data, char *msg, int exit_status);
void				welcome_screen(t_data *data, char *path);
void				clean_menus(t_data *data);
int				parse_doors(t_data *data);
t_door				*get_door_at(t_data *data, int map_x, int map_y);
void				doors_interaction(t_player *player, t_door *doors,
						int doors_nbr, t_data *data);

#endif
