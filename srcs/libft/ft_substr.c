/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:51:55 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 16:25:21 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str || !s)
		return (NULL);
	i = 0;
	while (len-- > 0)
	{
		if (start >= ft_strlen(s))
			return (str);
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
