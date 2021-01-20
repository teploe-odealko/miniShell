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
	if (flags && *flags)
	{
		if (ft_streq(flags[0], "-n"))
		{
			if (flags[1] != NULL)
				ft_putstr_fd(flags[1], 1);
		}
		else
		{
			ft_putstr_fd(flags[0], 1);
			ft_putstr_fd("\n", 1);
		}
	}
}
