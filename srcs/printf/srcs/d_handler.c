/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:03:37 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/19 14:08:32 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_prec_num(long long nb, int prec)
{
	if (nb < 0)
		ft_putchar('-');
	while (prec-- - absnumlen(nb, 10) > 0)
		ft_putchar('0');
	ft_putnbr(nb, 10);
}

void		d_handler(t_par *par, va_list *args)
{
	int			is_neg;
	char		fill;
	long long	nb;

	fill = par->zero == 1 ? '0' : ' ';
	nb = va_arg(*args, int);
	is_neg = nb < 0 ? 1 : 0;
	if (par->prec == 0 && nb == 0)
		print_fill(fill, par->wid);
	else if (par->minus == 1)
	{
		print_prec_num(nb, par->prec);
		print_fill(' ', par->wid -
		(maxint(par->prec, absnumlen(nb, 10)) + is_neg));
	}
	else if (par->prec >= 0 || fill == ' ')
	{
		print_fill(fill,
		par->wid - (maxint(par->prec, absnumlen(nb, 10)) + is_neg));
		print_prec_num(nb, par->prec);
	}
	else
		print_prec_num(nb, par->wid - is_neg);
}
