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

char	*ft_key_plus_value(t_pair *pair)
{
	char	*tmp;
	char	*tmpr;

	tmp = ft_strjoin(pair->key, "=");
	tmpr = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp = ft_strjoin(tmpr, pair->value);
	free(tmpr);
	tmpr = ft_strjoin(tmp, "\"");
	free(tmp);
	return (tmpr);
}

void	ft_print_export(t_pair *pair, int len)
{
	char	**env;
	int		i;

	i = 0;
	len = ft_lstsize(pair);
	if (!(env = (char **)malloc(sizeof(char *) * (len + 1))))
		critical_errors_handler(strerror(errno));
	while (pair && i < len)
	{
		if (pair->key && pair->value && pair->value[0] == '\0')
			env[i] = ft_substr(pair->key, 0, ft_strlen(pair->key));
		else if (pair->key)
			env[i] = ft_key_plus_value(pair);
		i++;
		pair = pair->next;
	}
	env[i] = NULL;
	bubble_sort(env, len);
	i = 0;
	while (i < len)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	free_2darray(env);
}

int		ft_valid_env(char **flags, int j, int i, int *plus)
{
	while (flags[j][i] && flags[j][i] != '=')
	{
		if (flags[j][i] == '+' || flags[j][i] == '_' ||
		(flags[j][i] >= 65 && flags[j][i] <= 90) ||
			(flags[j][i] >= 97 && flags[j][i] <= 122))
		{
			if (flags[j][i] == '+' && flags[j][i + 1] == '=')
				*plus = 1;
			else if (flags[j][i] == '+')
				ft_print_inv(flags, j);
		}
		else
		{
			ft_print_inv(flags, j);
			break ;
		}
		i++;
	}
	return (i);
}

void	ft_export_or_set_value(t_dict *dict, char **flags, int j)
{
	int		plus;
	char	*tmp;
	int		i;

	plus = 0;
	i = ft_valid_env(flags, j, 0, &plus);
	tmp = ft_substr(flags[j], 0, i - plus);
	if (i - plus != 0 && !get_value_by_key(dict, tmp))
		add_new_key(dict, tmp,
					ft_substr(flags[j] + i + 1, 0,
					ft_strlen(flags[j] + i + 1)));
	else if (i != 0)
	{
		if (plus)
			set_value_by_key(dict, tmp,
			ft_strjoin(get_value_by_key(dict, tmp), flags[j] + i + 1));
		else if (flags[j][i + 1] != '\0')
			set_value_by_key(dict, tmp, ft_substr(flags[j] + i + 1, 0,
			ft_strlen(flags[j] + i + 1)));
		free(tmp);
	}
}

void	ft_export(t_dict *dict, char **flags)
{
	int		j;
	t_pair	*pair;

	j = 0;
	pair = dict->pair;
	if (!*flags)
		ft_print_export(pair, 0);
	else
		while (flags && flags[j])
		{
			ft_export_or_set_value(dict, flags, j);
			j++;
		}
}
