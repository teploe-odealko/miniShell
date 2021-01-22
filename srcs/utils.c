/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:18:54 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 18:18:55 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_center(char *line, int i, int j)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(line) - (j - i) + 1));
	if (!res)
		critical_errors_handler(strerror(errno));
	ft_strlcpy(res, line, i + 1);
	ft_strlcat(res, line + j, (ft_strlen(line) - (j - i) + 1));
	return (res);
}

void	free_2darray(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	check_exit_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
}

int		index_before_spec_char(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|'
		|| str[i] == ' ' || str[i] == '$' || str[i] == '\''
		|| str[i] == '"' || ft_isdigit(str[i]))
			return (i - 1);
		i++;
	}
	return (i);
}

void	del_front(t_pair **pair)
{
	t_pair	*tmp;

	tmp = *pair;
	*pair = (*pair)->next;
	free(tmp->key);
	free(tmp);
}
