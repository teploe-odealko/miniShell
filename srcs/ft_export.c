/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:48:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/16 15:48:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void    ft_export(t_dict *dict, char **flags, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!*flags)
	{
		NULL;
	}
	else if (flags[0][0] == '-' || (flags[0][0] >= 65 && flags[0][0] <= 90) ||
	(flags[0][0] >= 97 && flags[0][0] <= 122))
	{
		while (flags[0][i] && flags[0][i] != '=')
			i++;
		tmp = ft_substr(flags[0], 0, i);
		if (!get_value_by_key(dict, tmp))
			add_new_key(dict, tmp,
			  ft_substr(flags[0] + i + 1, 0,
			   ft_strlen(flags[0] + i + 1)));
		else
		{
			set_value_by_key(dict, tmp, ft_substr(flags[0] + i + 1, 0,
												  ft_strlen(flags[0] + i + 1)));
		}
	}
	else
	{
		ft_putstr_fd("export: `", fd);
		ft_putstr_fd(flags[0], fd);
		ft_putstr_fd("': not a valid identifier\n", fd);
	}
}