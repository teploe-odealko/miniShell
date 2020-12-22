/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:10:00 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/01 18:10:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int n;
	int	i;

	if (!s || !fd)
		return ;
	i = 0;
	n = (int)ft_strlen(s);
	while (i < n)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
