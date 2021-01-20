/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:37:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/15 21:37:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_key_and_value(struct s_dict *self, int fd)
{
	t_pair *tmp;

	tmp = self->pair;
	while (tmp)
	{
		if (tmp->key && tmp->value && tmp->value[0] != '\0')
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(tmp->value, fd);
			ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
	}
}

void    ft_env(t_dict *dict, char ** flags)
{
	if (flags[0] != NULL)
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(flags[0], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		g_status = 127;
	}
	else
		print_key_and_value(dict, 1);
}