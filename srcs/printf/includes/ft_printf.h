/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:54:22 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 11:17:08 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include <stdarg.h>
# include "parser.h"
# include <stdlib.h>
# include <unistd.h>

int		g_putcount;
void	per_handler(t_par *par, char c);
int		ft_printf(const char *format, ...);
void	ft_putchar(char c);
void	processor(t_par *par, va_list *args);
void	d_handler(t_par *par, va_list *args);
void	u_handler(t_par *par, va_list *args);
void	x_handler(t_par *par, va_list *args);
void	xcap_handler(t_par *par, va_list *args);
void	s_handler(t_par *par, char *s);
void	p_handler(t_par *par, va_list *args);
void	c_handler(t_par *par, char c);
void	print_fill(char fill, int wid);
int		absnumlen(long long nb, int base);
int		maxint(int a, int b);
int		minint(int a, int b);
void	ft_putnbr(long n, int base);
int		ft_moving_atoi(char **str);

#endif
