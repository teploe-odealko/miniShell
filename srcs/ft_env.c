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
#include <unistd.h>

void	print_key_and_value(struct s_dict *self, int fd)
{
	t_pair *tmp;

	tmp = self->pair;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(tmp->value, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
}

void    ft_env(t_dict *dict, char **flags, int fd)
{
	print_key_and_value(dict, fd);
}