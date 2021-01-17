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

int 	ft_min(int a, int b)
{
	return a < b ? a : b;
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

void 	bubble_sort(char **env, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		if (ft_strncmp(env[i], env[i + 1], ft_min(lofk(env[i]), lofk(env[i + 1]))) > 0)
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
		env[len] = NULL;
		while (i < len)
		{
			if (pair->value[0] == '\0')
				env[i] = ft_substr(pair->key, 0, ft_strlen(pair->key));
			else
			{
				tmp = ft_strjoin(pair->key, "=");
				tmpr = ft_strjoin(tmp, "\"");
				free(tmp);
				tmp = ft_strjoin(tmpr, pair->value);
				free(tmpr);
				env[i] = ft_strjoin(tmp, "\"");
				free(tmp);
			}
			i++;
			pair = pair->next;
		}
		bubble_sort(env, len);
		i = 0;
		while (i < len)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
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
