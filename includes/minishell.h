#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include "errno.h"

extern int		g_status;
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
	t_pair			*quotes;
}					t_dict;

int 				g_status;

void    		ft_echo(char **flags);
void    		ft_cd(t_dict *dict, char **flags);
void    		ft_pwd(t_dict *dict, char **flags);
void    		ft_export(t_dict *dict, char **flags);
void    		ft_unset(t_dict *dict, char **flags);
void    		ft_env(t_dict *dict, char **flags);
void    		ft_exit(char **flags);

char			*get_value_by_key(struct s_dict *self, char *key);
void			set_value_by_key(struct s_dict *self, char *key, char *value);
void			add_new_key(struct s_dict *self, char *key, char *value);
//void			parse_and_add(t_dict *self, char *s);
void 			remove_key(struct s_dict *self, char *key);
t_dict			*new_dict();
char			**from_dict(t_dict *dict);

void			insert_quotes_content(char **command, t_pair *prths, int i);
int				quotes_handler(char **line, t_pair **quotes);
char			*cut_center(char *line, int i, int j);
int				index_before_spec_char(char *str);
void			replace_vars(char **str, t_dict *dict);
char			*cut_off_word(char **str, int start, int finish, char *trim_set);
int 			cut_off_right_redirect(char **command, int i);
void			free_2darray(char **array);
void			check_exit_status(int status);
void			exec_other(char **command, t_dict *dict);
int 			cut_off_left_redirect(char **command, int i);
void			run_cmd(char **command, t_pair **prths, t_dict *dict);
void			switcher(char **command, t_dict *dict);
void			errors_handler(char *error_desc);
void			del_front(t_pair **pair);
void			command_decomp(char **command, t_dict *dict);
void			pipe_handler_parent(int pid, int *pipe_fd,
							char **command, char *right_com);
void			pipe_handler_children(int *pipe_fd, t_dict *dict, char *left_com);

void			critical_errors_handler(char *error_desc);
t_dict			*set_env_to_dict(char **envs);
void			close_pipe(int *fd, int *fd1);
void			ft_list_remove_if(t_pair **begin_list, void *key_ref, int (*cmp)());

void			ft_ctrl_int(int signal);
void			ft_ctrl_quit(int signal);

#endif
