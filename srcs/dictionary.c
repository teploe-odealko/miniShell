#include "minishell.h"
//  TODO : реализации функций



static	void	parse_and_add(struct s_dict *self, char *s)
{
	t_pair *new_pair;
	int 	i;

	i = 0;
	new_pair = malloc(sizeof(t_pair));
	while (s[i] && s[i] != '=')
		i++;
	//  дальше в new_pair.key и value делаем ft_strdup
}


// конструктор
t_dict 			*new_dict(char **env)
{
	t_dict	*dict;

	dict = NULL;
	while(env != NULL)
	{
//		parse_and_add();
		env++;
	}
//	dict->add_new_key = add_new_key;
//	dict->get_value_by_key = ;
//	dict->set_value_by_key = ;
//	dict->add_new_key = ;
//	dict->remove_key = ;

	return (dict);
}
