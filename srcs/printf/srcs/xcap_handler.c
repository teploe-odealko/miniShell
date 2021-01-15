/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcap_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:47:48 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/18 21:12:14 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_putnbr_16_cap(unsigned int num)
{
	if (num >= 16)
	{
		ft_putnbr_16_cap(num / 16);
		ft_putnbr_16_cap(num % 16);
	}
	else if (num < 10)
		ft_putchar(num + '0');
	else
		ft_putchar(num - 10 + 'A');
}

static void		print_prec_num(unsigned int nb, int prec)
{
	while (prec-- - absnumlen(nb, 16) > 0)
		ft_putchar('0');
	ft_putnbr_16_cap(nb);
}

void			xcap_handler(t_par *par, va_list *args)
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
