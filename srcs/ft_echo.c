/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:48:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/15 20:48:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **flags)
{
	int	i;

	i = 0;
	if (flags && flags[i])
	{
		if (ft_streq(flags[0], "-n"))
		{
			i = 1;
			while (flags[i])
			{
				ft_putstr_fd(flags[i], 1);
				if (flags[i + 1] != NULL)
					ft_putstr_fd(" ", 1);
				i++;
			}
		}
		else
		{
			while (flags[i])
			{
				ft_putstr_fd(flags[0], 1);
				if (flags[i + 1] != NULL)
					ft_putstr_fd(" ", 1);
				i++;
			}
			ft_putstr_fd("\n", 1);
		}
	}
	else
		ft_putstr_fd("\n", 1);
}
