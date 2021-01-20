/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 13:43:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/16 13:43:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_unset(t_dict *dict, char **flags)
{
	int i;

	i = 0;
	while (flags && flags[i])
	{
//		if (flags[i][0] != '\0')
		if (i == 9)
		{
			printf("%d\n", i);
		}
		remove_key(dict, flags[i]);
		i++;
	}
}