/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:11:00 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/01 19:11:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pair 	*ft_lstnew(void* key, void *value)
{
    t_pair *tmp;

	tmp = (t_pair *)malloc(sizeof(t_pair));
	if (!tmp)
		critical_errors_handler(strerror(errno));
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}
