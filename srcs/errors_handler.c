/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 20:05:02 by ptycho            #+#    #+#             */
/*   Updated: 2021/01/22 18:12:40 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors_handler(char *error_desc)
{
	ft_putstr_fd(error_desc, 2);
	ft_putstr_fd("\n", 2);
}

void	critical_errors_handler(char *error_desc)
{
	ft_putstr_fd(error_desc, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
