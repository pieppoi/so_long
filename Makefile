# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 17:09:39 by mkazuhik          #+#    #+#              #
#    Updated: 2025/09/26 13:23:01 by mkazuhik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# System Detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLXFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz -lbsd
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

MLX = $(MLX_DIR)/libmlx.a

# Optional ft_printf (contains libft)
FT_PRINTF_DIR = ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a
# Detect if ft_printf is available
USE_FT_PRINTF := $(shell [ -f $(FT_PRINTF_DIR)/Makefile ] && echo 1 || echo 0)

# Include paths
INCLUDE = -I$(SRC_DIR) -I$(MLX_DIR)
ifeq ($(USE_FT_PRINTF),1)
INCLUDE += -I$(FT_PRINTF_DIR)
endif

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

# If ft_printf is not available, use local minimal libft
ifeq ($(USE_FT_PRINTF),0)
SRCS += libft.c
endif

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

$(NAME): $(OBJS) $(MLX) $(if $(filter 1,$(USE_FT_PRINTF)),$(FT_PRINTF_LIB))
	@echo "$(YELLOW)Compiling $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAGS) $(if $(filter 1,$(USE_FT_PRINTF)),$(FT_PRINTF_LIB))
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

$(FT_PRINTF_LIB):
	@echo "$(YELLOW)Compiling ft_printf...$(NC)"
	@$(MAKE) -C $(FT_PRINTF_DIR)
	@echo "$(GREEN)✓ ft_printf compiled$(NC)"

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
ifeq ($(USE_FT_PRINTF),1)
	@$(MAKE) clean -C $(FT_PRINTF_DIR)
endif
	@echo "$(GREEN)✓ Clean completed$(NC)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
ifeq ($(USE_FT_PRINTF),1)
	@$(MAKE) fclean -C $(FT_PRINTF_DIR)
endif
	@echo "$(GREEN)✓ Full clean completed$(NC)"

re: fclean all

# Include dependencies
-include $(DEPS)