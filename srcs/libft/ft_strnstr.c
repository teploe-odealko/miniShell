/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:04:59 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 20:23:53 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t nlen;

	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	while (*haystack && nlen <= len--)
	{
		if (!ft_strncmp(haystack, needle, nlen))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
