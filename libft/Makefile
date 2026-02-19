# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 11:29:52 by ilemos-c          #+#    #+#              #
#    Updated: 2026/02/17 19:56:54 by ingrid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

INCLUDES = -I$(INC_DIR)

# Colors
RESET =\033[0m
GREEN =\033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
BLUE = \033[0;34m

# Files
SRCS = $(SRC_DIR)/ft_atoi.c \
	$(SRC_DIR)/ft_bzero.c \
	$(SRC_DIR)/ft_calloc.c \
	$(SRC_DIR)/ft_isalnum.c \
	$(SRC_DIR)/ft_isalpha.c \
	$(SRC_DIR)/ft_isascii.c \
	$(SRC_DIR)/ft_isdigit.c \
	$(SRC_DIR)/ft_isprint.c \
	$(SRC_DIR)/ft_itoa.c \
	$(SRC_DIR)/ft_lstadd_back_bonus.c \
	$(SRC_DIR)/ft_lstadd_front_bonus.c \
	$(SRC_DIR)/ft_lstclear_bonus.c \
	$(SRC_DIR)/ft_lstdelone_bonus.c \
	$(SRC_DIR)/ft_lstlast_bonus.c \
	$(SRC_DIR)/ft_lstnew_bonus.c \
	$(SRC_DIR)/ft_lstsize_bonus.c \
	$(SRC_DIR)/ft_memchr.c \
	$(SRC_DIR)/ft_memcmp.c \
	$(SRC_DIR)/ft_memcpy.c \
	$(SRC_DIR)/ft_memmove.c \
	$(SRC_DIR)/ft_memset.c \
	$(SRC_DIR)/ft_putchar_fd.c \
	$(SRC_DIR)/ft_putendl_fd.c \
	$(SRC_DIR)/ft_putnbr_fd.c \
	$(SRC_DIR)/ft_putstr_fd.c \
	$(SRC_DIR)/ft_split.c \
	$(SRC_DIR)/ft_strchr.c \
	$(SRC_DIR)/ft_strdup.c \
	$(SRC_DIR)/ft_striteri.c \
	$(SRC_DIR)/ft_strjoin.c \
	$(SRC_DIR)/ft_strlcat.c \
	$(SRC_DIR)/ft_strlcpy.c \
	$(SRC_DIR)/ft_strlen.c \
	$(SRC_DIR)/ft_strmapi.c \
	$(SRC_DIR)/ft_strncmp.c \
	$(SRC_DIR)/ft_strnstr.c \
	$(SRC_DIR)/ft_strrchr.c \
	$(SRC_DIR)/ft_strtrim.c \
	$(SRC_DIR)/ft_substr.c \
	$(SRC_DIR)/ft_tolower.c \
	$(SRC_DIR)/ft_toupper.c \
	$(SRC_DIR)/ft_printf_basic.c \
	$(SRC_DIR)/ft_printf_pointer.c \
	$(SRC_DIR)/ft_printf_unsigned_hex.c \
	$(SRC_DIR)/ft_printf.c \
	$(SRC_DIR)/get_next_line.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)[OK]$(RESET) $(NAME) compiled successfully."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/libft.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)[CLEAN]$(RESET) libft/$(OBJ_DIR) removed."

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[FCLEAN]$(RESET) '$(NAME)' removed."

re: fclean all

.PHONY: all clean fclean re
