/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:13:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/22 18:36:10 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_pair **lst, void (*del)(void *))
{
	t_pair *tmp;
	t_pair *prev_tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	prev_tmp = *lst;
	while (prev_tmp != NULL)
	{
		tmp = prev_tmp;
		prev_tmp = prev_tmp->next;
		(tmp->key) ? (*del)(tmp->key) : NULL;
		(tmp->value) ? (*del)(tmp->value) : NULL;
		free(tmp);
	}
	*lst = NULL;
}
