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

void		ft_err_and_cd_home(t_dict *dict, char **flags, char *pwd, char *tmp)
{
	if (!flags[0] || (flags[0] && flags[0][0] == '~'))
	{
		if (!chdir(get_value_by_key(dict, "HOME")))
		{
			if (!get_value_by_key(dict, "OLDPWD"))
				add_new_key(dict, "OLDPWD", ft_substr(pwd, 0, ft_strlen(pwd)));
			else
				set_value_by_key(dict, "OLDPWD",
					ft_substr(pwd, 0, ft_strlen(pwd)));
			tmp = getcwd(NULL, 4096);
			set_value_by_key(dict, "PWD", ft_substr(tmp, 0, ft_strlen(tmp)));
			free(tmp);
		}
		else
			write(1, "HOME not set\n", 13);
	}
	else
	{
		ft_putstr_fd("cd: ", 1);
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(flags[0], 1);
		ft_putstr_fd("\n", 1);
		g_status = 1;
	}
}

void		ft_cd(t_dict *dict, char **flags)
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
		tmp = NULL;
		ft_err_and_cd_home(dict, flags, pwd, tmp);
	}
}
