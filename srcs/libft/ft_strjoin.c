/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:54:19 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 14:39:46 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <string.h>

char	*ft_adition(unsigned int n, unsigned m, char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (n + m + 1));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < m)
	{
		str[i + j] = s2[j];
		j++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	n;
	unsigned int	m;
	char			*str;

	if (!s1)
		return (NULL);
	if (!s2)
		return ((char*)s1);
	n = (unsigned int)ft_strlen(s1);
	m = (unsigned int)ft_strlen(s2);
	if ((str = ft_adition(n, m, s1, s2)))
		str[n + m] = '\0';
	return (str);
}
