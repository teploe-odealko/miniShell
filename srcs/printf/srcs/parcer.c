/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:07:21 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 15:11:06 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		parse_prec(char **format, va_list *args)
{
	int param;

	param = -1;
	if (**format == '.')
	{
		(*format)++;
		param = 0;
		if (**format == '*')
		{
			param = va_arg(*args, int);
			(*format)++;
		}
		else if ((**format >= '0' && **format <= '9') || **format == '-')
		{
			param = ft_atoi(format);
			if (param < 0)
				param = -1;
		}
	}
	return (param);
}

int		parse_width(char **format, va_list *args, t_par *par)
{
	int param;

	param = 0;
	if (**format == '*')
	{
		param = va_arg(*args, int);
		if (param < 0)
		{
			param *= -1;
			par->minus = 1;
		}
		(*format)++;
	}
	else if (**format >= '0' && **format <= '9')
		param = ft_atoi(format);
	return (param);
}

t_par	*pparser(char **format, va_list *args)
{
	t_par *par;

	if ((par = struct_creator()))
	{
		while (*(*format) == '-' || *(*format) == '0')
		{
			if (**format == '0')
				par->zero = 1;
			if (**format == '-')
				par->minus = 1;
			(*format)++;
		}
		if (par->minus == 1 && par->zero == 1)
			par->zero = 0;
		par->wid = parse_width(format, args, par);
		par->prec = parse_prec(format, args);
		par->type = **format;
		if (par->prec >= 0 && par->type != '%')
			par->zero = 0;
		(*format)++;
	}
	return (par);
}
