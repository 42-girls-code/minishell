# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/17 17:17:17 by ingrid            #+#    #+#              #
#    Updated: 2026/02/24 14:41:55 by ingrid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Valgrind
VALGRIND = valgrind

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=valgrind.supp

VALGRIND_STACK = $(VALGRIND_FLAGS) \
		--read-var-info=yes --vgdb=yes --trace-children=yes \
		--track-fds=yes

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = build
LIBFT_DIR = libft
LIBFT_INC = $(LIBFT_DIR)/inc

INCLUDES = -I$(INC_DIR) -I$(LIBFT_INC)

# Library
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

# Colors
RESET =\033[0m
GREEN =\033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m

# Files
SRCS = $(SRC_DIR)/minishell.c \
	$(SRC_DIR)/lexer/lex_handle_default_state.c \
	$(SRC_DIR)/lexer/lex_tokens.c \
	$(SRC_DIR)/lexer/lex_util.c \
	$(SRC_DIR)/lexer/lexer.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)[MiniShell]$(RESET) Linking objects..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)[OK]$(RESET) $(NAME) compiled successfully."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)[LIB]$(RESET) Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) --silent

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)[CLEAN]$(RESET) $(OBJ_DIR) removed."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent
	@echo "$(RED)[FCLEAN]$(RESET) '$(NAME)' removed."

re: fclean all

# norminette:📚
# 	@echo "$(BLUE)🧠 Running norminette...$(RESET)"
# 	@norminette $(SRCS) -R CheckForbiddenSourceHeader || true

.PHONY: all clean fclean re norminette valgrind
