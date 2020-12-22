/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:04:24 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 20:03:11 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
		{
			return ((char *)(str + i));
		}
		i++;
	}
	if (ch == '\0')
		return ((char *)(str + i));
	return (NULL);
}
