# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 19:14:42 by htharrau          #+#    #+#              #
#    Updated: 2025/04/07 12:51:21 by htharrau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
NAME_BONUS	= cub3D_bonus

SRCS_DIR	= src/
BONUS_DIR	= src_bonus/
OBJS_DIR	= obj/
OBJS_BONUS_DIR	= obj_bonus/
INCS_DIR	= inc/
INCS_BONUS_DIR	= inc_bonus/
LIBFT_DIR	= libft/
MLX_DIR		= MLX42/

LIBFT		= $(LIBFT_DIR)libft.a
MLX			= $(MLX_DIR)build/libmlx42.a

SRCS		= $(addprefix $(SRCS_DIR), init.c errors.c main.c welcome.c)       \
				$(addprefix $(SRCS_DIR)parsing/, a_parser.c e_trim_right.c     \
				d_trim_left.c g_valid_map.c f_valid_chars.c b_parse_elements.c \
				h_utils_parse.c c_save_map.c) 								   \
				$(addprefix $(SRCS_DIR)raycasting/, a_init_mlx.c b_loop_hook.c \
				c_update_fov.c  d_draw_ceiling_floor.c e_draw_walls.c		   \
				f_cast_rays.c g_textures.c m_resize_hook.c  l_escape.c		   \
				x_helper.c)
	   
SRCS_BONUS = $(addprefix $(BONUS_DIR), main.c) \
				$(addprefix $(BONUS_DIR)other/, doors_parse.c doors.c \
				init.c errors.c debug.c menus.c) \
				$(addprefix $(BONUS_DIR)parsing/, a_parser.c e_trim_right.c d_trim_left.c \
				g_valid_map.c f_valid_chars.c b_parse_elements.c h_utils_parse.c c_save_map.c) \
				$(addprefix $(BONUS_DIR)raycasting/, a_init_mlx.c d_draw_ceiling_floor.c \
				x_helper.c b_loop_hook.c e_draw_walls.c c_update_fov.c \
				f_cast_rays.c l_key_hooks.c g_draw_miniray.c h_draw_minimap.c i_textures.c \
				c_update_fov_utils.c f_cast_rays_utils.c m_resize_hook.c)

OBJS		= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJS_BONUS_DIR), $(SRCS_BONUS:.c=.o))

#-fsanitize=address
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -I$(MLX_DIR)/include -I$(LIBFT_DIR) -I$(INCS_DIR)
CFLAGS_BONUS = -Wall -Wextra -Werror -I$(MLX_DIR)/include -I$(LIBFT_DIR) -I$(INCS_BONUS_DIR)
LDFLAGS 	= -L$(LIBFT_DIR) -L$(MLX_DIR)/build -lft -lmlx42  -ldl -lglfw -pthread -lm
MAKE		= make --no-print-directory

.SILENT:

normal:			$(NAME)
all:			$(NAME) $(NAME_BONUS)
bonus:			$(NAME_BONUS)

$(NAME):		$(OBJS) $(LIBFT) $(MLX)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
				echo "$(MAGENTA)\n\n ██████╗██╗   ██╗██████╗ ██████╗ ██████╗\n██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \n$(DEFAULT)"

$(NAME_BONUS):	$(OBJS_BONUS) $(LIBFT) $(MLX)
				$(CC) $(CFLAGS_BONUS) $(OBJS_BONUS) -o $(NAME_BONUS) $(LDFLAGS)
				echo "$(WHITE)\n\n██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗\n██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝\n██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗\n██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║\n██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║\n╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝$(DEFAULT)"

$(OBJS_DIR)%.o: %.c 
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_BONUS_DIR)%.o: %.c 
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
				$(MAKE) -C $(LIBFT_DIR)
				echo "$(YELLOW)Libft created$(DEFAULT)"

$(MLX):
				cmake -B $(MLX_DIR)build -S $(MLX_DIR)
				$(MAKE) -C $(MLX_DIR)/build -j4
				echo "$(MINT)Minilibx created$(DEFAULT)"

clean:
				rm -rf $(OBJS_DIR)
				rm -rf $(OBJS_BONUS_DIR)
				make --no-print-directory -C $(LIBFT_DIR) clean
				rm -rf $(MLX_DIR)/build
				echo "$(ORANGE)Object files cleaned$(DEFAULT)"

fclean:			clean
				$(MAKE) -C $(LIBFT_DIR) fclean
				rm -f $(NAME)
				rm -f $(NAME_BONUS)
				echo "$(RED)Executable cleaned$(DEFAULT)"

re:				fclean all

.PHONY:			all normal bonus clean fclean re debug


#COLORS
# Define Custom Colors
RED = 		\033[1;31m
GREEN = 	\033[1;32m
YELLOW = 	\033[1;33m
BLUE = 		\033[1;34m
MAGENTA = 	\033[1;35m
CYAN = 		\033[1;36m
WHITE = 	\033[1;37m
DEFAULT = 	\033[0m
ORANGE = 	\033[1;38;2;255;165;0m

