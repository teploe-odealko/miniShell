cmake_minimum_required(VERSION 3.17)
project(shell C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(srcs/libft)

add_executable(shell
        includes/minishell.h
        srcs/libft/ft_atoi.c
        srcs/libft/ft_bzero.c
        srcs/libft/ft_calloc.c
        srcs/libft/ft_isalnum.c
        srcs/libft/ft_isalpha.c
        srcs/libft/ft_isascii.c
        srcs/libft/ft_isdigit.c
        srcs/libft/ft_isprint.c
        srcs/libft/ft_itoa.c
        srcs/libft/ft_lstadd_back.c
        srcs/libft/ft_lstadd_front.c
        srcs/libft/ft_lstclear.c
        srcs/libft/ft_lstdelone.c
        srcs/libft/ft_lstiter.c
        srcs/libft/ft_lstlast.c
        srcs/libft/ft_lstmap.c
        srcs/libft/ft_lstnew.c
        srcs/libft/ft_lstsize.c
        srcs/libft/ft_memccpy.c
        srcs/libft/ft_memchr.c
        srcs/libft/ft_memcmp.c
        srcs/libft/ft_memcpy.c
        srcs/libft/ft_memmove.c
        srcs/libft/ft_memset.c
        srcs/libft/ft_putchar_fd.c
        srcs/libft/ft_putendl_fd.c
        srcs/libft/ft_putnbr_fd.c
        srcs/libft/ft_putstr_fd.c
        srcs/libft/ft_split.c
        srcs/libft/ft_strchr.c
        srcs/libft/ft_strdup.c
        srcs/libft/ft_strjoin.c
        srcs/libft/ft_strlcat.c
        srcs/libft/ft_strlcpy.c
        srcs/libft/ft_strlen.c
        srcs/libft/ft_strmapi.c
        srcs/libft/ft_strncmp.c
        srcs/libft/ft_strnstr.c
        srcs/libft/ft_strrchr.c
        srcs/libft/ft_strtrim.c
        srcs/libft/ft_substr.c
        srcs/libft/ft_tolower.c
        srcs/libft/ft_toupper.c
        srcs/libft/get_next_line.c
        srcs/libft/ft_streq.c
        srcs/libft/ft_max.c
        srcs/libft/libft.h
        srcs/dictionary.c
        srcs/errors_handler.c
        srcs/minishell.c
        srcs/parser.c
        srcs/envs.c
        srcs/ft_echo.c
        srcs/ft_cd.c
        srcs/ft_pwd.c
        srcs/ft_env.c
        srcs/ft_list_remove_if.c
        srcs/ft_unset.c
        srcs/ft_export.c
        srcs/ft_exit.c
        srcs/ft_signal.c
        srcs/quotes.c
        srcs/utils.c
        srcs/exec.c
        srcs/dict_utils.c
        srcs/ft_export_utils.c
        srcs/dollar.c srcs/cut_str.c srcs/command_decomposition.c srcs/run_cmd.c)

target_compile_options(shell PRIVATE -Wall -Wextra -Werror)


