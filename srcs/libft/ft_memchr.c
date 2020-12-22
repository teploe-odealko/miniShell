/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:03:50 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/30 10:19:42 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*t;

	i = 0;
	t = s;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			return ((void*)(t + i));
		}
		i++;
	}
	return (0);
}
