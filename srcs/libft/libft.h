/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:07:05 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/01 15:00:02 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 128

# include <stddef.h>
# include "stdlib.h"

typedef struct		s_pair
{
	char 			*key;
	char 			*value;
	struct s_pair	*next;
}					t_pair;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strnstr(const char *haystack, const char *needle,
																size_t len);
char				*ft_strchr(const char *str, int ch);
char				*ft_strrchr(const char *str, int ch);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
long long			ft_atoi(const char *str);
int					ft_isalpha(int ch);
int					ft_isdigit(int ch);
int					ft_isalnum(int ch);
int					ft_isascii(int ch);
int					ft_isprint(int ch);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(long long n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_pair              *ft_lstnew(void* key, void *value);
void				ft_lstadd_front(t_pair **lst, t_pair *new);
int					ft_lstsize(t_pair *lst);
t_pair				*ft_lstlast(t_pair *lst);
void				ft_lstadd_back(t_pair **lst, t_pair *new);
void				ft_lstdelone(t_pair *lst, void (*del)(void *));
void				ft_lstclear(t_pair **lst, void (*del)(void *));
void				ft_lstiter(t_pair *lst, void (*f)(void *));
t_pair				*ft_lstmap(t_pair *lst, void *(*f)(void *),
													void (*del)(void *));
int					get_next_line(int fd, char **line);
int					ft_max(int a, int b);
int					ft_streq(char *s1, char *s2);

#endif
