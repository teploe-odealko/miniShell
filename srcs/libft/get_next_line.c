/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:04:00 by ptycho            #+#    #+#             */
/*   Updated: 2020/11/03 12:04:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

int		ft_strdel(int fd, char **save)
{
	if (save[fd])
	{
		free(save[fd]);
		save[fd] = NULL;
	}
	return (-1);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (1 + ft_strlen(s1)));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		get_oneline(int fd, char **line, char **save)
{
	int		i;
	char	*temp;

	i = 0;
	while (save[fd][i] != '\n' && save[fd][i] != '\0')
		i++;
	if (save[fd][i] == '\n')
	{
		if (!(*line = ft_substr(save[fd], 0, i)))
			return (ft_strdel(fd, save));
		if (!(temp = ft_strdup(&save[fd][i + 1])))
			return (ft_strdel(fd, save));
		free(save[fd]);
		save[fd] = temp;
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup(save[fd])))
			return (ft_strdel(fd, save));
		free(save[fd]);
		save[fd] = NULL;
		return (0);
	}
}

int		get_next_line(int fd, char **line)
{
	int				l;
	char			buff[BUFFER_SIZE + 1];
	static char		*save[256];
	char			*temp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buff, 0) < 0)
		return (-1);
	if (!save[fd])
		if (!(save[fd] = ft_strdup("")))
			return (-1);
	while (!ft_strchr(save[fd], '\n') && (l = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[l] = '\0';
		if (!(temp = ft_strjoin(save[fd], buff)))
			return (ft_strdel(fd, save));
		free(save[fd]);
		save[fd] = temp;
	}
	return (save[fd] == NULL ? 0 : get_oneline(fd, line, save));
}
