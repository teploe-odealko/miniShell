/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:49:47 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 10:49:06 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_correct_type(char type)
{
	if (type == 'd' || type == 'i' || type == 'u' || type == 's' ||
	type == 'x' || type == 'X' || type == 'p' || type == '%' || type == 'c')
		return (1);
	return (0);
}

static int	free_par(t_par *par)
{
	free(par);
	return (-1);
}

int			ft_printf(const char *format, ...)
{
	va_list args;
	t_par	*par;

	g_putcount = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!(par = pparser(((char**)&format), &args)))
				return (-1);
			if (!is_correct_type(par->type))
				return (free_par(par));
			processor(par, &args);
			free(par);
		}
		else
		{
			ft_putchar(*format);
			format++;
		}
	}
	va_end(args);
	return (g_putcount);
}
