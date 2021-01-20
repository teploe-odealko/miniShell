/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:59:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/19 11:59:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	ft_ctrl_int(int signal)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, WNOHANG);
	if (signal == SIGINT)
	{
		if (pid)
		{
			ft_putstr_fd(" \b\b \b\b \b\b", 1);
			write(1, "\n", 1);
			ft_putstr_fd("minishell-1.3$ ", 1);
			g_status = 1;
		}
		else
		{
			write(1, "\n", 1);
			g_status = 130;
		}
	}
}

void 	ft_ctrl_quit(int signal)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, WNOHANG);
	if (!pid)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_status = 131;
	}
	else
	{
		ft_putstr_fd(" \b\b \b\b", 1);
		g_status = 0;
	}
	(void)signal;
}
