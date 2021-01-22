/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:56:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/22 18:35:53 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_pair	*ft_lstmap(t_pair *lst, void *(*f)(void *), void (*del)(void *))
{
	t_pair	*new;
	t_pair	*temp;

	new = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		if ((temp = ft_lstnew(f(lst->key), f(lst->value))))
			ft_lstadd_back(&new, temp);
		else
			ft_lstclear(&new, del);
		lst = lst->next;
	}
	return (new);
}
