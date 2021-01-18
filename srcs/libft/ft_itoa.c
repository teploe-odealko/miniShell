/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:36:39 by ptycho            #+#    #+#             */
/*   Updated: 2020/10/31 19:30:10 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*ft_from(char *str, long long n, int len)
{
	long long	m;

	m = n;
	if (n < 0)
	{
		str[0] = '-';
		m = -n;
	}
	while (len--)
	{
		str[len] = m % 10 + '0';
		m /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa_special(char *str, char *tra)
{
	int	n;

	str[11] = '\0';
	n = 10;
	while (tra[n])
	{
		str[n] = tra[n];
		n--;
	}
	return (str);
}

char	*ft_itoa(long long n)
{
	long long		m;
	int				len;
	char			*str;

	m = n;
	len = 0;
	if (n <= 0)
		len = 1;
	while (m != 0)
	{
		len++;
		m /= 10;
	}
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n == (-9223372036854775807 - 1))
		str = ft_itoa_special(str, "-9223372036854775808");
	else
	{
		str = ft_from(str, n, len);
		str[len] = '\0';
	}
	return (str);
}
