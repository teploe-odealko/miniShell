/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:18:00 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/01 17:18:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	size_t			slen;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	str = malloc(sizeof(char) * (slen + 1));
	if (!str)
		critical_errors_handler(strerror(errno));
	while (i < slen)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[slen] = '\0';
	return (str);
}
