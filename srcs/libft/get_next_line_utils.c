/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:05:00 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/03 12:05:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

char	*ft_strchr(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str && str[i])
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	n;

	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	n = ft_strlen(s);
	while (len-- > 0)
	{
		if (start >= n)
			return (str);
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
