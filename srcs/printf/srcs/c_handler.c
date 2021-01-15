/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 23:28:31 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/18 21:04:56 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	c_handler(t_par *par, char c)
{
	if (par->minus == 1)
	{
		ft_putchar(c);
		print_fill(' ', par->wid - 1);
	}
	else
	{
		print_fill(' ', par->wid - 1);
		ft_putchar(c);
	}
}
