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

void    ft_export(t_dict *dict, char **flags)
{
	int		i;
	int 	len;
	char	*tmp;
	char 	**env;
	char 	*tmpr;
	t_pair	*pair;

	i = 0;
	pair = dict->pair;
	if (!*flags)
	{
		len = ft_lstsize(pair);
		env = (char **)malloc(sizeof(char *) * (len + 1));
		while (i < len)
		{
			tmp = ft_strjoin(pair->key, "=");
			tmpr = ft_strjoin(tmp, "\"");
			free(tmp);
			tmp = ft_strjoin(tmpr, pair->value);
			free(tmpr);
			env[i] = ft_strjoin(tmp, "\"");
			free(tmp);
			i++;
			pair = pair->next;
		}
	}
	else if (flags[0][0] == '_' || (flags[0][0] >= 65 && flags[0][0] <= 90) ||
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
			free(tmp);
		}
	}
	else
	{
		ft_putstr_fd("export: `", 1);
		ft_putstr_fd(flags[0], 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
	}
}
