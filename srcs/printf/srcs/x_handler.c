/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:16:02 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/19 12:22:47 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_prec_num(unsigned int nb, int prec)
{
	while (prec-- - absnumlen(nb, 16) > 0)
		ft_putchar('0');
	ft_putnbr(nb, 16);
}

void		x_handler(t_par *par, va_list *args)
{
	char			fill;
	unsigned int	nb;

	fill = par->zero == 1 ? '0' : ' ';
	nb = va_arg(*args, unsigned int);
	if (par->prec == 0 && nb == 0)
		print_fill(fill, par->wid);
	else if (par->minus == 1)
	{
		print_prec_num(nb, par->prec);
		print_fill(' ', par->wid - (maxint(par->prec, absnumlen(nb, 16))));
	}
	else if (par->prec >= 0 || fill == ' ')
	{
		print_fill(fill, par->wid - (maxint(par->prec, absnumlen(nb, 16))));
		print_prec_num(nb, par->prec);
	}
	else
		print_prec_num(nb, par->wid);
}
