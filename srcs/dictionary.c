#include "minishell.h"
//  TODO : реализации функций

void			add_new_key(struct s_dict *self, char *key, char *value)
{
	if (key && value)
		ft_lstadd_back(&self->pair, ft_lstnew(key, value));
}

char			*get_value_by_key(struct s_dict *self, char *key)
{
	t_pair *tmp;

	tmp = self->pair;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
}

static	void	parse_and_add(t_pair **head, char *env)
{
	t_pair	*new_pair;
	int		j;

	new_pair = malloc(sizeof(t_pair));
	j = 0;
	while (env[j] != '=')
		j++;
	new_pair->key = ft_substr(env, 0, j);
	new_pair->value = ft_substr(env + j + 1, 0, ft_strlen(env + j + 1));
	ft_lstadd_back(head, ft_lstnew(new_pair->key, new_pair->value));
	free(new_pair);
	//  дальше в new_pair.key и value делаем ft_strdup
}

// конструктор
t_dict			*new_dict(char **env)
{
	t_dict	*dict;
	t_pair	*head;
	t_pair	*new_pair;
	int		j;

	dict = NULL;
	head = NULL;
	new_pair = malloc(sizeof(t_pair));
	while(env && *env != NULL)
	{
		parse_and_add(&head, *env);
		env++;
	}
	free(new_pair);
	dict->pair = head;
	dict->add_new_key = add_new_key;
	dict->get_value_by_key = get_value_by_key;
//	dict->set_value_by_key = ;
//	dict->add_new_key = ;
//	dict->remove_key = ;
	return (dict);
}
