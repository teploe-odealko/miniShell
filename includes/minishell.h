#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include "libft.h"

typedef struct	s_elements
{
	char		**env_var;

}				t_elements;

void    ft_echo(t_elements *elm, char **flags, int fd);
void    ft_cd(t_elements *elm, char **flags, int fd);
void    ft_pwd(t_elements *elm, char **flags, int fd);
void    ft_export(t_elements *elm, char **flags, int fd);
void    ft_unset(t_elements *elm, char **flags, int fd);
void    ft_env(t_elements *elm, char **flags, int fd);
void    ft_exit(t_elements *elm, char **flags, int fd);

typedef struct		s_dict
{
	char			*(*get_value_by_key)(struct s_dict *self, char *key);
	void			(*set_value_by_key)(struct s_dict *self, char *key, char *value);
	void			(*add_new_key)(struct s_dict *self, char *key, char *value);
	void 			(*remove_key)(struct s_dict *self, char *key);
	t_pair			*pair;
}					t_dict;

char			*get_value_by_key(struct s_dict *self, char *key);
void			set_value_by_key(struct s_dict *self, char *key, char *value);
void			add_new_key(struct s_dict *self, char *key, char *value);
//void			parse_and_add(t_dict *self, char *s);
void 			remove_key(struct s_dict *self, char *key);
t_dict			*new_dict();
void			errors_handler(char *error_desc);
t_dict			*set_env_to_dict(char **envs);

#endif
