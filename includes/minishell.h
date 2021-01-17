#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>
#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include "errno.h"

typedef struct	s_elements
{
	char		**env_var;

}				t_elements;

typedef struct		s_dict
{
	char			*(*get_value_by_key)(struct s_dict *self, char *key);
	void			(*set_value_by_key)(struct s_dict *self, char *key, char *value);
	void			(*add_new_key)(struct s_dict *self, char *key, char *value);
	void 			(*remove_key)(struct s_dict *self, char *key);
	t_pair			*pair;
}					t_dict;

void    ft_echo(t_dict *dict, char **flags);
void    ft_cd(t_dict *dict, char **flags);
void    ft_pwd(t_dict *dict, char **flags);
void    ft_export(t_dict *dict, char **flags);
void    ft_unset(t_dict *dict, char **flags);
void    ft_env(t_dict *dict);
void    ft_exit(t_dict *dict, char **flags);

char			*get_value_by_key(struct s_dict *self, char *key);
void			set_value_by_key(struct s_dict *self, char *key, char *value);
void			add_new_key(struct s_dict *self, char *key, char *value);
//void			parse_and_add(t_dict *self, char *s);
void 			remove_key(struct s_dict *self, char *key);
t_dict			*new_dict();
void			errors_handler(char *error_desc);
t_dict			*set_env_to_dict(char **envs);

void			ft_list_remove_if(t_pair **begin_list, void *key_ref, int (*cmp)());

#endif
