/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:10:03 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 19:10:11 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		index_before_spec_char_redirect(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|'
			|| str[i] == ' ' || str[i] == '$' || str[i] == '\''
			|| str[i] == '"')
			return (i - 1);
		i++;
	}
	return (i);
}

int		smcln(char *res)
{
	while (*res)
	{
		if ((*res == ';' && *(res + 1) == ';') || (*res == '<' && *(res + 1) == '<')
		|| (*res == '>' && *(res + 1) == '>' &&
		*(res + 1) != '\0' && *(res + 2) == '>'))
			return (1);
		res++;
	}
	return (0);
}
