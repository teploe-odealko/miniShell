/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:02:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/15 13:02:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void    ft_pwd(t_dict *dict, char **flags, int fd)
{
	char *pwd;

	if (flags)
		NULL;
	pwd = get_value_by_key(dict, "PWD");
	write(fd, pwd, ft_strlen(pwd));
	write(fd, "\n", 1);
}