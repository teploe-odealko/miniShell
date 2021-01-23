/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:58:31 by bashleig          #+#    #+#             */
/*   Updated: 2021/01/22 18:34:43 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_moving_atoi(char **str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (*(*str) == ' ' || *(*str) == '\t' || *(*str) == '\n' ||
			*(*str) == '\r' || *(*str) == '\v' || *(*str) == '\f')
		(*str)++;
	if (*(*str) == '-')
		sign = -1;
	if (*(*str) == '-' || *(*str) == '+')
		(*str)++;
	while (*(*str) >= '0' && *(*str) <= '9')
	{
		res = res * 10 + *(*str) - '0';
		(*str)++;
	}
	return (sign * res);
}

void	ft_putchar(char c)
{
	extern int g_putcount;

	write(1, &c, 1);
	g_putcount++;
}

t_par	*struct_creator(void)
{
	t_par *par;

	par = (t_par*)malloc(sizeof(t_par));
	if (!par)
		critical_errors_handler(strerror(errno));
	par->zero = 0;
	par->minus = 0;
	par->prec = -1;
	par->type = 'n';
	par->wid = -1;
	return (par);
}

void	print_fill(char fill, int wid)
{
	while (wid-- > 0)
		ft_putchar(fill);
}

int		absnumlen(long long nb, int base)
{
	int			len;
	long long	nb_unsign;

	nb_unsign = (nb < 0) ? nb * -1 : nb;
	len = 0;
	if (nb_unsign == 0)
		return (1);
	while (nb_unsign > 0)
	{
		nb_unsign /= base;
		len++;
	}
	return (len);
}
