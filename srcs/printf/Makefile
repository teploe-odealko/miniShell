# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bashleig <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 12:28:49 by bashleig          #+#    #+#              #
#    Updated: 2020/11/20 11:18:19 by bashleig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

# directories
SRC_DIR  = srcs
HEADER  = includes
OBJ_DIR  = obj

SRCS = ft_printf.c \
			parcer.c \
			utils.c \
			utils2.c \
			processor.c \
			d_handler.c \
			x_handler.c \
			xcap_handler.c \
			p_handler.c \
			s_handler.c \
			c_handler.c \
			u_handler.c \
			per_handler.c

OBJ		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

includes = $(wildcard includes/*.h)

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I$(HEADER)

# rules
all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(includes)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re