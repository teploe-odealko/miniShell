/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:07:00 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/01 20:07:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_pair *lst, void (*del)(void *))
{
	if (!lst)
		return ;
    (*del)(lst->key);
    (*del)(lst->value);
	free(lst);
}
