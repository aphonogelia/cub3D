# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htharrau <htharrau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 19:14:42 by htharrau          #+#    #+#              #
#    Updated: 2025/03/12 19:13:51 by htharrau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

SRCS_DIR	= src/
PARSE_DIR	= $(SRCS_DIR)parsing/
RAYCAST_DIR	= $(SRCS_DIR)raycasting/
TEXTURE_DIR = $(SRCS_DIR)textures/
BONUS_DIR 	= $(SRCS_DIR)bonus/
OBJS_DIR	= obj/
INCS_DIR	= inc/
LIBFT_DIR	= libft/
MLX_DIR		= MLX42/

LIBFT		= $(LIBFT_DIR)libft.a
MLX			= $(MLX_DIR)build/libmlx42.a

SRCS		= $(addprefix $(PARSE_DIR), parser.c  trim_right.c trim_left.c \
				valid_map.c valid_chars.c parse_elements.c  utils_parse.c) \
			  $(addprefix $(RAYCAST_DIR),  a_init_mlx.c  d_draw_ceiling_floor.c \
			   g_draw_miniray.c  x_helper.c b_loop_hook.c   e_draw_walls.c  \
			   h_draw_minimap.c  z_cleanup.c c_update_fov.c  f_cast_rays.c  \
			   l_escape.c) \
			  $(addprefix $(SRCS_DIR), init.c errors.c main.c debug.c) \
			  $(addprefix $(TEXTURE_DIR), draft.c textures.c) \
			  $(addprefix $(BONUS_DIR), mouse.c doors.c)

OBJS		= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -I$(MLX_DIR)/include -I$(LIBFT_DIR) -I$(INCS_DIR)
LDFLAGS 	= -L$(LIBFT_DIR) -L$(MLX_DIR)/build -lft -lmlx42  -ldl -lglfw -pthread -lm
##LDFLAGS 	= -L$(LIBFT_DIR) -L$(MLX_DIR)/build  -ldl -lglfw -pthread -lm
##gcc main.c ... libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
MAKE		= make --no-print-directory

.SILENT:

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT) $(MLX)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
				echo "$(MAGENTA)\n\n ██████╗██╗   ██╗██████╗ ██████╗ ██████╗\n██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \n$(DEFAULT)"

$(OBJS_DIR)%.o: %.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
				$(MAKE) -C $(LIBFT_DIR)
				echo "$(MAGENTA)Libft created$(DEFAULT)"

$(MLX):
				cmake -B $(MLX_DIR)build -S $(MLX_DIR)
				$(MAKE) -C $(MLX_DIR)/build -j4
				echo "$(MAGENTA)Minilibx created$(DEFAULT)"

clean:
				$(MAKE) -C $(LIBFT_DIR) clean
				echo "$(YELLOW)Libft cleaned$(DEFAULT)"
				rm -rf $(MLX_DIR)/build
				echo "$(YELLOW)Minilibx cleaned$(DEFAULT)"
				rm -rf $(OBJS_DIR)/
				echo "$(YELLOW)Object files cleaned$(DEFAULT)"

fclean:			clean
				$(MAKE) -C $(LIBFT_DIR) fclean
				rm -f $(NAME)
				echo "$(ORANGE)Executable cleaned$(DEFAULT)"

re:				fclean all


debug:			CFLAGS += -fsanitize=address -fno-omit-frame-pointer -g
debug:			re

help:
				@echo "Available targets:"
				@echo "  all     : Build the project"
				@echo "  clean   : Remove object files"
				@echo "  fclean  : Remove all generated files"
				@echo "  re      : Rebuild the project"
				@echo "  debug   : Build with address sanitizer"


.PHONY:			all clean fclean re debug help


#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
DEFAULT = \033[0m
ORANGE = \033[1;38;2;255;165;0m

