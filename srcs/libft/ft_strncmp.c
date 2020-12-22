/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:04:45 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/01 15:28:29 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const char *cs1;
	const char *cs2;

	cs1 = s1;
	cs2 = s2;
	if (n < 0)
		return (0);
	while ((*cs1 || *cs2) && n--)
	{
		if (*cs1 != *cs2)
			return (*(unsigned char*)(cs1) - *(unsigned char*)(cs2));
		cs1++;
		cs2++;
	}
	return (0);
}
