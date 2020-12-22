/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:45:00 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/01 19:45:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pair 	*ft_lstlast(t_pair *lst)
{
    t_pair	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
