/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:41:47 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 17:42:31 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_off_word(char **str, int start, int finish, char *trim_set)
{
	char	*res;
	char	*tmp;
	char	*tmp2;
	int		cutted_len;

	cutted_len = (int)ft_strlen(*str) - (finish - start) + 1;
	res = ft_substr(*str, start, finish - start + 1);
	tmp = *str;
	*str = malloc(sizeof(char) * cutted_len);
	if (!*str)
		critical_errors_handler(strerror(errno));
	ft_bzero(*str, cutted_len);
	ft_strlcat(*str, tmp, start);
	ft_strlcat(*str, tmp + finish + 1, cutted_len);
	free(tmp);
	tmp = ft_strtrim(res, trim_set);
	tmp2 = *str;
	*str = ft_strtrim(tmp2, trim_set);
	free(tmp2);
	free(res);
	return (tmp);
}

int		cut_off_right_redirect(char **command, int i)
{
	int		j;
	int		fd;
	char	*filename;

	j = i + 1;
	if ((*command)[j] == '>')
	{
		j++;
		filename = cut_off_word(command, j,
				j + index_before_spec_char_redirect(&((*command)[j])), " ");
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else
	{
		filename = cut_off_word(command, j,
				j + index_before_spec_char_redirect(&((*command)[j])), " ");
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (fd < 0)
		errors_handler(strerror(errno));
	free(filename);
	return (fd);
}

int		cut_off_left_redirect(char **command, int i)
{
	int		j;
	int		fd;
	char	*filename;

	j = i + 1;
	filename = cut_off_word(command, j,
			j + index_before_spec_char_redirect(&((*command)[j])), " ");
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd < 0)
		errors_handler(strerror(errno));
	return (fd);
}
