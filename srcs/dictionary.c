/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 00:11:13 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/21 00:11:15 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"
#include "errno.h"

void	add_new_key(struct s_dict *self, char *key, char *value)
{
	t_pair *new_pair;

	if (self && key && value)
	{
		if (!(new_pair = ft_lstnew(key, value)))
			errors_handler(strerror(errno));
		ft_lstadd_back(&self->pair, new_pair);
	}
}

char	*get_value_by_key(struct s_dict *self, char *key)
{
	t_pair *tmp;

	tmp = self->pair;
	while (tmp && tmp->key)
	{
		if (ft_streq(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_value_by_key(struct s_dict *self, char *key, char *value)
{
	t_pair *tmp;

	tmp = self->pair;
	while (tmp && tmp->key)
	{
		if (ft_streq(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
}

void	remove_key(struct s_dict *self, char *key)
{
	ft_list_remove_if(&self->pair, key, &ft_streq);
}

t_dict	*new_dict(void)
{
	t_dict	*dict;

	if (!(dict = (t_dict*)malloc(sizeof(t_dict))))
		critical_errors_handler(strerror(errno));
	dict->pair = NULL;
	dict->add_new_key = add_new_key;
	dict->get_value_by_key = get_value_by_key;
	dict->remove_key = remove_key;
	return (dict);
}
