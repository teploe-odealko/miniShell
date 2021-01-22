/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:03:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/22 18:38:39 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_min(int a, int b)
{
	return (a < b ? a : b);
}

size_t	lofk(const char *str)
{
	size_t i;

	i = 0;
	while (str && str[i] != '=')
	{
		i++;
	}
	return (i);
}

void	bubble_sort(char **env, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		if (env && env[i] && ft_strncmp(env[i], env[i + 1],
			ft_min(lofk(env[i]), lofk(env[i + 1]))) > 0)
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	ft_print_inv(char **flags, int j)
{
	ft_putstr_fd("export: `", 1);
	ft_putstr_fd(flags[j], 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
	g_status = 1;
}
