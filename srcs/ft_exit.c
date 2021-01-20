/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:56:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/18 11:56:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/errno.h>

extern int errno;

int 	ft_is_numeric(char *flags)
{
	int			i;
	int			len;
	long long	alp;

	i = 0;
	alp = 0;
	len = ft_strlen(flags);
	if (len > 20)
		return (0);
	while (flags && flags[i])
	{
		if (!(ft_isdigit(flags[i]) || flags[0] == '-' || flags[0] == '+'))
			return (0);
		i++;
	}
	if (len == 20 && !(flags[0] == '-' || flags[0] == '+'))
		return (0);
	if ((len == 20 && (flags[0] == '-' || flags[0] == '+')) || len == 19)
	{
		alp = ft_atoi(flags);
		if (!ft_streq(ft_itoa(alp), flags))
			return (0);
	}
	return (1);
}

void    ft_exit(char **flags)
{
	int			i;
	int			j;
	long long	alp;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (flags[0] && flags[1])
	{
		while (flags[i])
		{
			j = 0;
			while (flags[i][j])
			{
				if (!ft_isdigit(flags[i][j]))
				{
					ft_putstr_fd("bash: exit: ", 1);
					ft_putstr_fd(flags[0], 1);
					ft_putstr_fd(": numeric argument required\n", 1);
					exit(255);
				}
				j++;
			}
			i++;
		}
		ft_putstr_fd("bash: exit: too many arguments\n", 1);
		g_status = 1;
	}
	else if (flags[0] && ft_is_numeric(flags[0]) == 0)
	{
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(flags[0], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
	else
	{
		alp = 0;
		if (flags[0] != NULL)
			alp = ft_atoi(flags[0]);
		exit((unsigned char)alp);
	}
}
