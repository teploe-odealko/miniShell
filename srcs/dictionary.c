#include "minishell.h"

#include "string.h"
#include "errno.h"
//  TODO : реализации функций

void			add_new_key(struct s_dict *self, char *key, char *value)
{
	t_pair *new_pair;

	if (self && key && value)
		if (!(new_pair = ft_lstnew(key, value)))
			errors_handler(strerror(errno));
		ft_lstadd_back(&self->pair, new_pair);
}

char			*get_value_by_key(struct s_dict *self, char *key)
{
	t_pair *tmp;

	tmp = self->pair;
	while (tmp)
	{
		if (ft_streq(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_dict			*new_dict()
{
	t_dict	*dict;

	if (!(dict = (t_dict*)malloc(sizeof(t_dict))))
		errors_handler(strerror(errno));
	dict->pair = NULL;
	dict->add_new_key = add_new_key;
	dict->get_value_by_key = get_value_by_key;
//	dict->set_value_by_key = ;
//	dict->add_new_key = ;
//	dict->remove_key = ;
	return (dict);
}
