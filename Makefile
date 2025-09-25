# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 17:09:39 by mkazuhik          #+#    #+#              #
#    Updated: 2025/09/23 19:27:27 by mkazuhik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# System Detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLXFLAGS = -Lminilibx-linux -lmlx -L./libft -lft -lXext -lX11 -lm -lz
	MLX_DIR = minilibx-linux
endif
ifeq ($(UNAME_S), Darwin)
	MLXFLAGS = -Lminilibx-macos -lmlx -framework OpenGL -framework AppKit
	MLX_DIR = minilibx-macos
endif

# Directories
SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/
MAP_DIR = maps/
TEXTURE_DIR = textures/

# Libraries
LIBFT = libft/libft.a

MLX = $(MLX_DIR)/libmlx.a

# Include paths
INCLUDE = -I$(INC_DIR) -I$(MLX_DIR) -Ilibft

# Source files
SRCS = main.c \
	   ft_check_map.c \
	   ft_close_game.c \
	   ft_free_memory.c \
	   ft_handle_input.c \
	   ft_init_game.c \
	   ft_init_map.c \
	   ft_render_map.c \
       ft_utils.c \
       ft_path_check.c \
	   get_next_line.c

# Object files
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# Dependencies
DEPS = $(OBJS:.o=.d)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Compiling $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAGS)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"

$(MLX):
	@echo "$(YELLOW)Compiling MiniLibX...$(NC)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)✓ MiniLibX compiled$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $<$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(NC)"
	@make -C libft
	@echo "$(GREEN)✓ libft compiled$(NC)"

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make clean -C libft
	@echo "$(GREEN)✓ Clean completed$(NC)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "$(GREEN)✓ Full clean completed$(NC)"

re: fclean all

# Include dependencies
-include $(DEPS)