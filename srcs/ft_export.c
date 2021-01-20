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
		if (env && env[i] && ft_strncmp(env[i], env[i + 1], ft_min(lofk(env[i]), lofk(env[i + 1]))) > 0)
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

//void 	ft_change_value(t_dict *dict, char **flags, char *tmp, int plus)
//{
//	int		j;
//	int 	i;
//
//	j = 0;
//	while (flags && flags[j])
//	{
//		if (flags[j][0] == '_' || (flags[j][0] >= 65 && flags[j][0] <= 90) ||
//			(flags[j][0] >= 97 && flags[j][0] <= 122)) {
//			while (flags[j][i] && flags[j][i] != '=')
//			{
//				if (flags[j][i] == '+' && flags[j][i + 1] == '=')
//					plus = 1;
//				i++;
//			}
//			tmp = ft_substr(flags[j], 0, i - plus);
//			if (i != 0 && !get_value_by_key(dict, tmp))
//				add_new_key(dict, tmp,
//							ft_substr(flags[j] + i + 1, 0,
//									  ft_strlen(flags[j] + i + 1)));
//			else if (i != 0)
//			{
//				if (plus)
//				{
//					set_value_by_key(dict, tmp,
//									 ft_strjoin(get_value_by_key(dict, tmp), flags[j] + i + 1));
//				}
//				else if (flags[j][ + i + 1] != '\0')
//					set_value_by_key(dict, tmp, ft_substr(flags[j] + i + 1, 0,
//														  ft_strlen(flags[j] + i + 1)));
//				free(tmp);
//			}
//		}
//		else
//		{
//			ft_putstr_fd("export: `", 1);
//			ft_putstr_fd(flags[j], 1);
//			ft_putstr_fd("': not a valid identifier\n", 1);
//			g_status = 1;
//		}
//		j++;
//	}
//}

void    ft_export(t_dict *dict, char **flags)
{
	int		i;
	int		j;
	int 	len;
	char	*tmp;
	char 	**env;
	char 	*tmpr;
	t_pair	*pair;
	int 	plus;

	j = 0;
	i = 0;
	plus = 0;
	pair = dict->pair;
	if (!*flags)
	{
		len = ft_lstsize(pair);
		env = (char **)malloc(sizeof(char *) * (len + 1));
		if (!env)
			critical_errors_handler(strerror(errno));
		while (pair && i < len)
		{
			if (pair->key && pair->value && pair->value[0] == '\0')
				env[i] = ft_substr(pair->key, 0, ft_strlen(pair->key));
			else if (pair->key)
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
		env[i] = NULL;
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
	else
		while (flags && flags[j])
		{
			if (flags[j][0] == '_' || (flags[j][0] >= 65 && flags[j][0] <= 90) ||
					 (flags[j][0] >= 97 && flags[j][0] <= 122))
			{
				while (flags[j][i] && flags[j][i] != '=')
				{
					if (flags[j][i] == '+' && flags[j][i + 1] == '=')
						plus = 1;
					i++;
				}
				tmp = ft_substr(flags[j], 0, i - plus);
				if (i != 0 && !get_value_by_key(dict, tmp))
					add_new_key(dict, tmp,
								ft_substr(flags[j] + i + 1, 0,
										  ft_strlen(flags[j] + i + 1)));
				else if (i != 0)
				{
					if (plus)
					{
						set_value_by_key(dict, tmp,
					   ft_strjoin(get_value_by_key(dict, tmp), flags[j] + i + 1));
					}
					else if (flags[j][ + i + 1] != '\0')
						set_value_by_key(dict, tmp, ft_substr(flags[j] + i + 1, 0,
							ft_strlen(flags[j] + i + 1)));
					free(tmp);
				}
			}
			else
			{
				ft_putstr_fd("export: `", 1);
				ft_putstr_fd(flags[j], 1);
				ft_putstr_fd("': not a valid identifier\n", 1);
				g_status = 1;
			}
			j++;
		}
}
