/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:04:08 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 20:02:22 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = len - 1;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (s >= d)
		ft_memcpy(d, s, len);
	else
	{
		while (i + 1)
		{
			d[i] = s[i];
			i--;
		}
	}
	return (dst);
}
