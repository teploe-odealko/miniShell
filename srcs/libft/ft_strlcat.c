/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:04:30 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 16:43:30 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src,
		size_t dstsize)
{
	size_t dlen;
	size_t slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize < dlen + 1)
		return (dstsize + slen);
	if (dstsize - dlen > 0)
	{
		while (*dst)
			dst++;
		ft_strlcpy(dst, src, dstsize - dlen);
	}
	return (dlen + slen);
}
