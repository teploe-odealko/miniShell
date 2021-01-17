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

void    ft_pwd(t_dict *dict, char **flags)
{
	char	*pwd;
	if (flags && dict)
		NULL;

	pwd = getcwd(NULL, 2048);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}