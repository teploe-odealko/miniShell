/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 17:25:08 by ptycho            #+#    #+#             */
/*   Updated: 2020/08/05 20:04:32 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_list_remove(t_pair **begin_list, t_pair *temp, t_pair *temp_prev)
{
	if (*begin_list == temp)
	{
		*begin_list = temp->next;
		(temp->value) ? free(temp->value) : NULL;
		(temp->key) ? free(temp->key) : NULL;
		free(temp);
	}
	else if (temp->next == NULL)
	{
		if (temp_prev == NULL)
			*begin_list = NULL;
		else
			temp_prev->next = NULL;
		(temp->value) ? free(temp->value) : NULL;
		(temp->key) ? free(temp->key) : NULL;
		free(temp);
	}
	else
	{
		temp_prev->next = temp->next;
		(temp->value) ? free(temp->value) : NULL;
		(temp->key) ? free(temp->key) : NULL;
		free(temp);
	}
}

void	ft_list_remove_if(t_pair **begin_list, void *key_ref, int (*cmp)())
{
	t_pair	*temp;
	t_pair	*temp_prev;
	char	*key;

	key = key_ref;
	if (begin_list == NULL || *begin_list == NULL)
		return ;
	temp = *begin_list;
	while (temp != NULL)
	{
		if (temp->key != NULL)
			if ((*cmp)(temp->key, key_ref) != 0)
				ft_list_remove(begin_list, temp, temp_prev);
		temp_prev = temp;
		temp = temp->next;
	}
}
