/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:05:10 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 20:06:32 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	i;

	i = (int)ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == ch)
			return ((char*)(str + i));
		i--;
	}
	return (NULL);
}
