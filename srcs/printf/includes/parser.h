/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:08:15 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/18 20:38:57 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef	struct		s_pars{
	int				minus;
	int				zero;
	int				wid;
	int				prec;
	char			type;
}					t_par;
t_par				*pparser(char **format, va_list *args);
t_par				*struct_creator();

#endif
