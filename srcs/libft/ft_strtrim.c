/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:24:38 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 16:25:04 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*es1;
	char	*str;

	if (!s1)
		return (NULL);
	es1 = (char*)s1 + (int)ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (ft_strchr(set, *(es1 - 1)) && s1 != es1)
		es1--;
	str = (char*)malloc(sizeof(char) * (es1 - s1 + 1));
	ft_strlcpy(str, s1, sizeof(char) * (es1 - s1 + 1));
	return (str);
}
