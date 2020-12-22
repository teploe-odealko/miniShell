/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:55:02 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 20:36:57 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void *data;

	data = malloc(size * count);
	if (!data)
		return (NULL);
	ft_bzero(data, size * count);
	return (data);
}
