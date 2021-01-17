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
	char	*pwd;
//	char	*oldpwd;
	int 	len;

	len = ft_strlen(flags[0]);
	pwd = dict->get_value_by_key(dict, "PWD");
	//oldpwd = get_value_by_key(dict, "OLDPWD");
	if (!chdir(flags[0]))
	{
		set_value_by_key(dict, "OLDPWD", pwd);
		if (flags[0][0] != '/') {
			pwd = ft_strjoin(pwd, "/");
			while (flags[0][len - 1] == '/') {
				//flags[0][len - 1] = 0;
				len--;
			}
			set_value_by_key(dict, "PWD", ft_strjoin(pwd, flags[0]));
		}
		else
			set_value_by_key(dict, "PWD", ft_strjoin(pwd, flags[0]));
		//free(pwd);
	}
	else
	{
		write(fd, "cd: no such file or directory: ", 31);
		write(fd, flags[0], len);
		write(fd, "\n", 1);
	}
}