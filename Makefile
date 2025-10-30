# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/28 16:14:19 by abidaux           #+#    #+#              #
#    Updated: 2025/10/30 10:27:00 by abidaux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables de Base ---
NAME = cub3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# --- Bibliothèques ---
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# --- Dossiers ---
OBJ_DIR = obj
SRC_DIR = src

# --- Flags de Compilation ---
FULL_CFLAGS = $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lbsd

# --- Fichiers Source ---
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# --- Couleurs ---
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# --- Logique du Spinner ---
define run_with_spinner
	$(2) > /dev/null 2>&1 & \
	PID=$$!; \
	i=0; \
	while kill -0 $$PID 2>/dev/null; do \
		case $$((i % 4)) in \
			0) printf "\r$(1) [ ]$(RESET)   ";; \
			1) printf "\r$(1) [.]$(RESET)   ";; \
			2) printf "\r$(1) [..]$(RESET)  ";; \
			3) printf "\r$(1) [...]$(RESET) ";; \
		esac; \
		i=$$((i + 1)); \
		sleep 0.15; \
	done; \
	wait $$PID
endef

# --- Règles Principales ---

all: $(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(BLUE)Téléchargement de la libft...$(RESET)"
	@git clone https://github.com/4drie2/libft.git $(LIBFT_DIR) 2>/dev/null || (cd $(LIBFT_DIR) && git pull > /dev/null 2>&1)
	@echo "$(BLUE)Compilation de la libft...$(RESET)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)Libft compilée avec succès !$(RESET)"

$(MLX):
	@echo "$(BLUE)Téléchargement de la minilibx...$(RESET)"
	@git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR) 2>/dev/null || (cd $(MLX_DIR) && git pull > /dev/null 2>&1)
	@printf "$(BLUE)↪ Compilation de la minilibx... [ ]$(RESET)"
	@if $(call run_with_spinner,$(BLUE)↪ Compilation de la minilibx...,make -C $(MLX_DIR) --no-print-directory); then \
		printf "\r$(GREEN)✔ Minilibx compilée avec succès !                  $(RESET)\n"; \
	else \
		printf "\r$(RED)✖ Erreur lors de la compilation de la minilibx$(RESET)\n"; \
		exit 1; \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@printf "$(YELLOW)Compilation de %s... [ ]$(RESET)" "$<"
	@mkdir -p $(dir $@)
	@if $(call run_with_spinner,$(YELLOW)Compilation de $<...,$(CC) $(FULL_CFLAGS) -c $< -o $@); then \
		printf "\r$(GREEN)✔ Compilation de %s terminée                    $(RESET)\n" "$<"; \
	else \
		printf "\r$(RED)✖ Erreur de compilation de %s$(RESET)\n" "$<"; \
		exit 1; \
	fi

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Création de l'exécutable $(NAME)...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Compilation de $(NAME) terminée avec succès !$(RESET)"

# --- Règles de Nettoyage ---

clean:
	@echo "$(RED)Suppression des fichiers objets...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory > /dev/null 2>&1 || true
	@if [ -d "$(MLX_DIR)" ]; then \
		printf "$(RED)Nettoyage de la minilibx... [ ]$(RESET)"; \
		if $(call run_with_spinner,$(RED)Nettoyage de la minilibx...,make -C $(MLX_DIR) clean --no-print-directory); then \
			printf "\r$(GREEN)✔ Nettoyage de la minilibx terminé                    $(RESET)\n"; \
		else \
			printf "\r$(RED)✖ Erreur lors du nettoyage de la minilibx$(RESET)\n"; \
		fi; \
	fi
	@echo "$(GREEN)Nettoyage terminé !$(RESET)"

fclean: clean
	@echo "$(RED)Suppression de l'exécutable $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		printf "$(RED)Suppression de la libft... [ ]$(RESET)"; \
		if $(call run_with_spinner,$(RED)Suppression de la libft...,rm -rf $(LIBFT_DIR)); then \
			printf "\r$(GREEN)✔ Suppression de la libft terminée                    $(RESET)\n"; \
		else \
			printf "\r$(RED)✖ Erreur lors de la suppression de la libft$(RESET)\n"; \
		fi; \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		printf "$(RED)Suppression de la minilibx... [ ]$(RESET)"; \
		if $(call run_with_spinner,$(RED)Suppression de la minilibx...,rm -rf $(MLX_DIR)); then \
			printf "\r$(GREEN)✔ Suppression de la minilibx terminée                    $(RESET)\n"; \
		else \
			printf "\r$(RED)✖ Erreur lors de la suppression de la minilibx$(RESET)\n"; \
		fi; \
	fi
	@echo "$(GREEN)Nettoyage complet terminé !$(RESET)"

re: fclean all

.PHONY: all clean fclean re
