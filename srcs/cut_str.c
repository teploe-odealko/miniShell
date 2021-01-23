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

int		count_end(char *str, char *trim_set, int len)
{
	int count;

	count = 0;
	while (len)
	{
		if (str[len - 1] == trim_set[0] || str[len - 1] == trim_set[1])
			count++;
		else
			return (count);
		len--;
	}
	return (count);
}

char	*cut_off_word(char **str, int start, int finish, char *trim_set)
{
	char	*res;
	char	*tmp;
	int		cutted_len;

	res = ft_substr(*str, start, finish - start + 1);
	tmp = *str;
	cutted_len = (int)ft_strlen(*str) - (finish - start) + 1 - count_end(tmp, trim_set, start);
	*str = malloc(sizeof(char) * cutted_len);
	if (!*str)
		critical_errors_handler(strerror(errno));
	ft_bzero(*str, cutted_len);
	ft_strlcat(*str, tmp, start - count_end(tmp, trim_set, start) + 1);
	ft_strlcat(*str, tmp + finish + 1, cutted_len);
	free(tmp);
	if (ft_strchr(trim_set, '$'))
		tmp = ft_strtrim(res, trim_set);
	else
		tmp = ft_strtrim(res, " ");
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
				j + index_before_spec_char_redirect(&((*command)[j])), ">");
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else
	{
		filename = cut_off_word(command, j,
				j + index_before_spec_char_redirect(&((*command)[j])), ">");
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
			j + index_before_spec_char_redirect(&((*command)[j])), "<");
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd < 0)
		errors_handler(strerror(errno));
	return (fd);
}
