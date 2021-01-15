/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:14:09 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 11:10:34 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_prec_str(char *s, int prec)
{
	while (prec-- > 0 && *s)
	{
		ft_putchar(*s);
		s++;
	}
}

static size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

void			s_handler(t_par *par, char *s)
{
	int		prec;
	char	fill;

	if (!s)
		s = "(null)";
	fill = par->zero == 1 && *s == '%' ? '0' : ' ';
	prec = par->prec < 0 ? ft_strlen(s) : minint(par->prec, ft_strlen(s));
	if (par->minus == 1)
	{
		print_prec_str(s, prec);
		print_fill(fill, par->wid - prec);
	}
	else
	{
		print_fill(fill, par->wid - prec);
		print_prec_str(s, prec);
	}
}
