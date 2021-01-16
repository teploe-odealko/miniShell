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
#include "string.h"
#include "errno.h"

void    ft_cd(t_dict *dict, char **flags, int fd)
{
	char	pwd[2048];
	char	*tmp;

	getcwd(pwd, 2048);
	if (!chdir(flags[0]))
	{
		if (!get_value_by_key(dict, "OLDPWD"))
			add_new_key(dict, "OLDPWD", ft_substr(pwd, 0, ft_strlen(pwd)));
		else
			set_value_by_key(dict, "OLDPWD", ft_substr(pwd, 0, ft_strlen(pwd)));
		tmp = getcwd(NULL, 4096);
		set_value_by_key(dict, "PWD", ft_substr(tmp, 0, ft_strlen(tmp)));
		free(tmp);
	}
	else
	{
		if (!flags[0] || (flags[0] && flags[0][0] == '~'))
		{
			if (!chdir(get_value_by_key(dict, "HOME"))) {
				if (!get_value_by_key(dict, "OLDPWD"))
					add_new_key(dict, "OLDPWD", ft_substr(pwd, 0, ft_strlen(pwd)));
				else
					set_value_by_key(dict, "OLDPWD", ft_substr(pwd, 0, ft_strlen(pwd)));
				tmp = getcwd(NULL, 4096);
				set_value_by_key(dict, "PWD", ft_substr(tmp, 0, ft_strlen(tmp)));
				free(tmp);
			}
			else
				write(fd, "HOME not set\n", 13);
		}
		else
		{
			ft_putstr_fd("cd: ", fd);
			ft_putstr_fd(strerror(errno), fd);
			ft_putstr_fd(": ", fd);
			ft_putstr_fd(flags[0], fd);
			ft_putstr_fd("\n", fd);
		}
	}
}