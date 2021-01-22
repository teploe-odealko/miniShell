/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:10:54 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 18:11:00 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_vars1(char **str, int i, t_dict *dict, char **value)
{
	char *key;

	if ((*str)[i + 1] == '?')
	{
		*value = ft_itoa(g_status);
		key = ft_strdup("?");
	}
	else if (ft_isdigit((*str)[i + 1]))
	{
		key = cut_off_word(str, i + 1,
				i + 2 + index_before_spec_char(&((*str)[i + 1])), " $");
		*value = ft_strdup(dict->get_value_by_key(dict, key));
	}
	else
	{
		key = cut_off_word(str, i + 1,
				i + 1 + index_before_spec_char(&((*str)[i + 1])), " $");
		*value = ft_strdup(dict->get_value_by_key(dict, key));
	}
	return (key);
}

void		replace_vars2(char **str, int i, t_dict *dict)
{
	char	*str_dup;
	char	*key;
	int		len;
	char	*tmp;
	char	*value;

	str_dup = ft_strdup(*str);
	key = replace_vars1(str, i, dict, &value);
	len = (int)(ft_strlen(str_dup) - ft_strlen(key) + ft_strlen(value));
	tmp = *str;
	*str = malloc(sizeof(char) * len);
	if (!*str)
		critical_errors_handler(strerror(errno));
	ft_bzero(*str, len);
	ft_strlcat(*str, str_dup, i + 1);
	ft_strlcat(*str, value, len);
	ft_strlcat(*str, str_dup + i + ft_strlen(key) + 1, len);
	free(str_dup);
	free(key);
	free(value);
	free(tmp);
}

void		replace_vars(char **str, t_dict *dict)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0')
			{
				i++;
				continue ;
			}
			replace_vars2(str, i, dict);
			continue ;
		}
		i++;
	}
}
