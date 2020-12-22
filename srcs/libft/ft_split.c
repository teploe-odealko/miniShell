/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:28:38 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 17:34:24 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	ft_mtclear(char **m, int n)
{
	int j;

	j = 0;
	while (j < n)
		free(m[j++]);
	free(m);
}

int		ft_wordlen(char const *s, int i, char c)
{
	int n;

	n = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		n++;
	}
	return (n);
}

int		linecount(char const *str, char c)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			n++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (n);
}

void	swp(char **dest, char const *str, int n, char c)
{
	int i;
	int j;
	int l;

	l = 0;
	i = 0;
	while (i < n)
	{
		while (str[l] != '\0' && str[l] == c)
			l++;
		j = ft_wordlen(str, l, c);
		if (j)
		{
			if ((!(dest[i] = (char *)malloc(sizeof(char) * (j + 1)))))
			{
				ft_mtclear(dest, n);
				return ;
			}
			j = 0;
			while (str[l] != '\0' && str[l] != c)
				dest[i][j++] = str[l++];
			dest[i][j] = '\0';
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		n;

	if (!s)
		return (NULL);
	n = linecount(s, c);
	if ((!(dest = (char**)malloc(sizeof(char *) * (n + 1)))))
		return (dest);
	dest[n] = NULL;
	swp(dest, s, n, c);
	return (dest);
}
