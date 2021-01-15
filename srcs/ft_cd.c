/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:22:00 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/15 13:22:00 by ptycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void    ft_cd(t_dict *dict, char **flags, int fd)
{
	char	pwd[4096];
	int 	len;

	getcwd(pwd, 4096);
	len = ft_strlen(flags[0]);
	if (!chdir(flags[0]))
	{
		if (!get_value_by_key(dict, "OLDWPD"))
			add_new_key(dict, "OLDPWD", pwd);
		else
			set_value_by_key(dict, "OLDPWD", pwd);
		set_value_by_key(dict, "PWD", flags[0]);
	}
	else
	{
		if (!flags[0] || (flags[0] && flags[0][0] == '~'))
		{
			if (!chdir(get_value_by_key(dict, "HOME"))) {
				if (!get_value_by_key(dict, "OLDWPD"))
					add_new_key(dict, "OLDPWD", pwd);
				else
					set_value_by_key(dict, "OLDPWD", pwd);
			}
			else
				write(fd, "HOME not set\n", 13);
		}
		else
		{
			write(fd, "cd: no such file or directory: ", 31);
			write(fd, flags[0], len);
			write(fd, "\n", 1);
		}
	}
}