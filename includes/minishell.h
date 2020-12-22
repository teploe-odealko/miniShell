#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>

typedef struct  s_elements
{
	char    **env_var;

}               t_elements;


/*
** Обработка ошибок происходит внутри функций
*/
void    ft_echo(t_elements *elm, char **flags, int fd);
void    ft_cd(t_elements *elm, char **flags, int fd);
void    ft_pwd(t_elements *elm, char **flags, int fd);
void    ft_export(t_elements *elm, char **flags, int fd);
void    ft_unset(t_elements *elm, char **flags, int fd);
void    ft_env(t_elements *elm, char **flags, int fd);
void    ft_exit(t_elements *elm, char **flags, int fd);

typedef struct		s_pair
{
	char 			*key;
	char 			*value;
	struct s_pair	*next;
}					t_pair;


typedef struct		s_dict
{
	char			*(*get_value_by_key)(struct s_dict *self, char *key);
	void			(*set_value_by_key)(struct s_dict *self, char *key, char *value);
	void			(*add_new_key)(struct s_dict *self, char *key, char *value);
//	void			(*parse_and_add)(struct s_dict *self, char *s);
	void 			(*remove_key)(struct s_dict *self, char *key);
	t_pair			*pair;
}					t_dict;

//Реализовать
char			*get_value_by_key(struct s_dict *self, char *key);
void			set_value_by_key(struct s_dict *self, char *key, char *value);
void			add_new_key(struct s_dict *self, char *key, char *value);
//void			parse_and_add(struct s_dict *self, char *s);
void 			remove_key(struct s_dict *self, char *key);


#endif //SHELL_MINISHELL_H
