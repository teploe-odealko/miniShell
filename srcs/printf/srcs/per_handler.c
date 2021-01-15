/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:13:48 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 11:49:03 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	per_handler(t_par *par, char c)
{
	char fill;

	fill = par->zero == 1 ? '0' : ' ';
	if (par->minus == 1)
	{
		ft_putchar(c);
		print_fill(' ', par->wid - 1);
	}
	else
	{
		print_fill(fill, par->wid - 1);
		ft_putchar(c);
	}
}
