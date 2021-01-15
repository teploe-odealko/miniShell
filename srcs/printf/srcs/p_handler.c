/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:59:35 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 15:45:41 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_prec_num(unsigned long long nb, int prec)
{
	int prec_cpy;

	prec_cpy = prec;
	ft_putchar('0');
	ft_putchar('x');
	if (prec != 0 || nb != 0)
		while (prec-- - absnumlen(nb, 16) > 0)
			ft_putchar('0');
	if (prec_cpy != 0 || nb != 0)
		ft_putnbr(nb, 16);
}

void		p_handler(t_par *par, va_list *args)
{
	char				fill;
	unsigned long long	nb;

	fill = par->zero == 1 ? '0' : ' ';
	nb = va_arg(*args, unsigned long long);
	if (par->prec == 0 && nb == 0)
		par->wid = par->wid + 1;
	if (par->minus == 1)
	{
		print_prec_num(nb, par->prec);
		print_fill(' ', par->wid - (maxint(par->prec + 2,
		absnumlen(nb, 16) + 2)));
	}
	else if (par->prec >= 0 || fill == ' ')
	{
		print_fill(fill, par->wid - (maxint(par->prec + 2,
		absnumlen(nb, 16) + 2)));
		print_prec_num(nb, par->prec);
	}
	else
		print_prec_num(nb, par->wid - 2);
}
