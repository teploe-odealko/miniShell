NAME = minishell

LIBFT_HEADER = srcs/libft

LIB_SRCS = ft_substr.c \
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
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstnew.c ft_lstsize.c \
		ft_streq.c ft_max.c ft_lstiter.c
LIB_OBJ = $(addprefix $(LIBFT_HEADER)/,$(LIB_SRCS:.c=.o))

SRCS =	srcs/dictionary.c \
		srcs/errors_handler.c \
		srcs/minishell.c \
		srcs/envs.c \
		srcs/ft_echo.c \
		srcs/ft_cd.c \
		srcs/ft_pwd.c \
		srcs/ft_env.c \
		srcs/ft_list_remove_if.c \
		srcs/ft_unset.c \
		srcs/ft_export.c \
		srcs/ft_exit.c \
		srcs/ft_signal.c \
		srcs/quotes.c \
		srcs/utils.c \
		srcs/exec.c \
		srcs/dict_utils.c \
		srcs/ft_export_utils.c \
		srcs/command_decomposition1.c \
		srcs/dollar.c \
		srcs/cut_str.c \
		srcs/command_decomposition.c \
		srcs/run_cmd.c \
		srcs/utils2.c

OBJ = $(SRCS:.c=.o)

LIBFT = srcs/libft/libft.a

INCLUDE = includes

HEADES = srcs/libft/libft.h includes/minishell.h

FLAG = -Wall -Wextra -Werror -I $(LIBFT_HEADER) -I $(INCLUDE)

all: $(NAME)

srcs/%.o:srcs/%.c $(HEADES)
	gcc $(FLAG) -o $@ -c $<

$(LIBFT_HEADER)/%.o:$(LIBFT_HEADER)/%.c $(LIBFT_HEADER)/libft.h
	@$(MAKE) -C $(LIBFT_HEADER)

$(NAME): $(OBJ) $(LIB_OBJ)
	@$(MAKE) -C $(LIBFT_HEADER)
	gcc $(FLAG) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	@$(MAKE) -C ./srcs/libft clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(LIBFT)
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
