/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:18:57 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 18:20:51 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd1(char **command_split, t_pair **prths, t_dict *dict, int i)
{
	int		j;

	j = 0;
	while (command_split[i][j])
	{
		if (command_split[i][j] == '"')
		{
			replace_vars(&(*prths)->key, dict);
			insert_quotes_content(&(command_split[i]), *prths, j);
			j += ft_strlen((*prths)->key);
			del_front(prths);
			continue ;
		}
		else if (command_split[i][j] == '\'')
		{
			insert_quotes_content(&(command_split[i]), *prths, j);
			j += ft_strlen((*prths)->key);
			del_front(prths);
			continue ;
		}
		j++;
	}
}

void	run_cmd(char **command, t_pair **prths, t_dict *dict)
{
	char	**command_split;
	int		i;

	i = 0;
	command_split = ft_split(*command, ' ');
	while (command_split[i])
	{
		run_cmd1(command_split, prths, dict, i);
		i++;
	}
	switcher(command_split, dict);
	free_2darray(command_split);
}
