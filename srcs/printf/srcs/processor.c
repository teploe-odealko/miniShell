/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:47:18 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 11:14:14 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	processor(t_par *par, va_list *args)
{
	if (par->type == 'd' || par->type == 'i')
		d_handler(par, args);
	else if (par->type == 'u')
		u_handler(par, args);
	else if (par->type == 's')
		s_handler(par, va_arg(*args, char*));
	else if (par->type == 'x')
		x_handler(par, args);
	else if (par->type == 'X')
		xcap_handler(par, args);
	else if (par->type == 'p')
		p_handler(par, args);
	else if (par->type == '%')
		per_handler(par, '%');
	else if (par->type == 'c')
		c_handler(par, (unsigned char)va_arg(*args, int));
}
