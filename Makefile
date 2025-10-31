# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 16:14:19 by abidaux           #+#    #+#              #
#    Updated: 2025/10/31 18:55:03 by abidaux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# --- Nom du Programme ---
NAME		= cub3d

# --- Compilateur et Flags ---
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
INCLUDES	= -I$(MLX_DIR) -I$(LIBFT_DIR) -Iinclude
LDFLAGS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lbsd

# --- Répertoires ---
SRC_DIR		= src
OBJ_DIR		= obj
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

# --- Bibliothèques ---
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a

# --- Fichiers ---
SRCS		= $(wildcard $(SRC_DIR)/*.c)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# --- Couleurs ---
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
RESET		= \033[0m

# --- Règles ---

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)✓ $(NAME) créé avec succès !$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(BLUE)Cloning libft...$(RESET)"; \
		git clone https://github.com/4drie2/libft.git $(LIBFT_DIR); \
	fi
	@echo "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ Libft compilée$(RESET)"

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(BLUE)Cloning minilibx...$(RESET)"; \
		git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)
	@echo "$(GREEN)✓ Minilibx compilée$(RESET)"

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi
	@echo "$(GREEN)✓ Clean done$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@rm -rf $(LIBFT_DIR) $(MLX_DIR)
	@echo "$(GREEN)✓ Full clean done$(RESET)"

re: fclean all

.PHONY: all clean fclean re
