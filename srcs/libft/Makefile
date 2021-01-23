# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptycho <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/01 14:00:52 by ptycho            #+#    #+#              #
#    Updated: 2020/11/01 14:00:58 by ptycho           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS            =   ft_substr.c \
                    ft_strlen.c \
                    ft_bzero.c \
                    ft_strjoin.c \
                    ft_strlcpy.c \
                    ft_strlcat.c \
                    ft_strtrim.c \
                    ft_strchr.c \
                    ft_split.c \
                    ft_strrchr.c \
                    ft_itoa.c \
                    ft_putchar_fd.c \
                    ft_putnbr_fd.c \
                    ft_strmapi.c \
                    ft_putstr_fd.c \
                    ft_putendl_fd.c \
                    ft_memset.c \
                    ft_memcpy.c \
                    ft_memccpy.c \
                    ft_memmove.c \
                    ft_memchr.c \
                    ft_memcmp.c \
                    ft_strncmp.c \
                    ft_strnstr.c \
                    ft_atoi.c \
                    ft_toupper.c \
                    ft_tolower.c \
                    ft_isalpha.c \
                    ft_isdigit.c \
                    ft_isascii.c \
                    ft_isprint.c \
                    ft_isalnum.c \
                    ft_calloc.c \
                    ft_strdup.c \
                    ft_streq.c ft_max.c ft_lstiter.c
BONUS           =   ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
                        ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
                        ft_lstmap.c ft_lstnew.c ft_lstsize.c \

OBJS            = $(SRCS:.c=.o)
BONUS_OBJS      = $(BONUS:.c=.o)
CC              = gcc
RM              = rm -f
CFLAGS          = -Wall -Wextra -Werror -I.
NAME            = libft.a

all: $(NAME)

%.o:%.c libft.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:         all clean fclean re bonus