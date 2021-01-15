/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:46:27 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/17 01:34:39 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		maxint(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int		minint(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	ft_putnbr(long n, int base)
{
	long long num;

	num = n < 0 ? (long long)(n * -1) : (long long)(n);
	if (num >= base)
	{
		ft_putnbr(num / base, base);
		ft_putnbr(num % base, base);
	}
	else if (num < 10)
		ft_putchar(num + '0');
	else
		ft_putchar(num - 10 + 'a');
}
