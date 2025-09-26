# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 17:09:39 by mkazuhik          #+#    #+#              #
#    Updated: 2025/09/27 03:19:27 by mkazuhik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# System Detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLXFLAGS = -Lminilibx-linux -lmlx -L./ft_printf -lftprintf -lXext -lX11 -lm -lz
	MLX_DIR = minilibx-linux
endif
ifeq ($(UNAME_S), Darwin)
	MLXFLAGS = -Lminilibx-macos -lmlx -framework OpenGL -framework AppKit
	MLX_DIR = minilibx-macos
endif

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
MAP_DIR = maps/
TEXTURE_DIR = textures/

# Libraries
FT_PRINTF = ft_printf/libftprintf.a

MLX = $(MLX_DIR)/libmlx.a

# Include paths
INCLUDE = -I$(SRC_DIR) -I$(MLX_DIR) -Ift_printf

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
       ft_map_rules.c \
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

$(NAME): $(OBJS) $(FT_PRINTF) $(MLX)
	@echo "$(YELLOW)Compiling $(NAME)...$(NC)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAGS)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"

$(MLX):
	@echo "$(YELLOW)Compiling MiniLibX...$(NC)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)✓ MiniLibX compiled$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $<$(NC)"
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(FT_PRINTF):
	@echo "$(YELLOW)Compiling ft_printf...$(NC)"
	@make -C ft_printf
	@echo "$(GREEN)✓ ft_printf compiled$(NC)"

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make clean -C ft_printf
	@echo "$(GREEN)✓ Clean completed$(NC)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make fclean -C ft_printf
	@echo "$(GREEN)✓ Full clean completed$(NC)"

re: fclean all

# Include dependencies
-include $(DEPS)