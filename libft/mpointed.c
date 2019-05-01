/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mpointed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:07:16 by jkellehe          #+#    #+#             */
/*   Updated: 2018/11/28 21:30:45 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void				str(va_list ap, char *format, t_ap *tree)
{
	char			*hold;
	wchar_t			*yeah;

	precision(format, ap, tree);
	if (THICC(tree->c))
	{
		yeah = va_arg(ap, wchar_t*);
		if (!yeah && !tree->z_pad)
			tree->ret += write(1, "(null)", 6);
		else if (!yeah)
			ft_wpad((wchar_t*)"\0", tree);
		else
			ft_wpad(yeah, tree);
		return ;
	}
	hold = va_arg(ap, char*);
	if (!hold && !tree->z_pad)
		tree->ret += write(1, "(null)", 6);
	else if (!hold)
		ft_putstr_fd_prec("\0", tree);
	else
		ft_putstr_fd_prec(hold, tree);
}

void				big_digit(va_list ap, char *format, t_ap *tree)
{
	intmax_t		holder;
	intmax_t		base;
	char			*delet;

	precision(format, ap, tree);
	base = 10;
	holder = 0;
	if (format[-1] == 'h')
		holder = (intmax_t)va_arg(ap, int);
	else if (format[0] == 'D')
		holder = (intmax_t)va_arg(ap, long);
	tree->neg = (holder < 0) ? (1) : (0);
	tree->zero = (holder == 0) ? (1) : (0);
	ft_putstr_fd_prec((delet = ft_maxtoa_base(holder, base, format)), tree);
	free(delet);
}

void				digit(va_list ap, char *format, t_ap *tree)
{
	intmax_t		holder;
	intmax_t		base;
	char			*delet;

	(precision(format, ap, tree) || (holder = 0));
	if (!(BASETEN(*format)) || !(base = 10))
		base = (format[0] == 'x' || format[0] == 'X') ? (16) : (2);
	base = (format[0] == 'o' || format[0] == 'O') ? (8) : (base);
	if (LL(format))
		holder = (intmax_t)va_arg(ap, long long);
	else if (format[-1] == 'l' || format[0] == 'D')
		holder = (intmax_t)va_arg(ap, long);
	else if (format[-1] == 'j')
		holder = (intmax_t)va_arg(ap, intmax_t);
	else if (format[-1] == 'z')
		holder = (intmax_t)va_arg(ap, size_t);
	else
		holder = (intmax_t)va_arg(ap, int);
	holder = (HH(format)) ? ((char)holder) : (holder);
	holder = (format[-1] == 'h') ? ((short)holder) : (holder);
	tree->neg = (holder < 0) ? (1) : (0);
	tree->zero = (holder == 0) ? (1) : (0);
	ft_putstr_fd_prec((delet = ft_maxtoa_base(holder, base, format)), tree);
	free(delet);
}

void				udigit(va_list ap, char *format, t_ap *tree)
{
	intmax_t		base;
	uintmax_t		uholder;

	if (!(BASETEN(*format)) || !(base = 10))
		base = (format[0] == 'x' || format[0] == 'X') ? (16) : (2);
	base = (format[0] == 'o' || format[0] == 'O') ? (8) : (base);
	if (format[0] == 'O')
		uholder = (uintmax_t)va_arg(ap, unsigned long);
	else if (IS_UNSIGN(format) && HH(format))
		uholder = (uintmax_t)(unsigned char)va_arg(ap, int);
	else if (format[-1] == 'h' && IS_UNSIGN(format))
		uholder = (uintmax_t)(unsigned short)va_arg(ap, int);
	else if (IS_UNSIGN(format) && LL(format))
		uholder = (uintmax_t)va_arg(ap, unsigned long long);
	else if (UDIGIT1(format))
		uholder = (uintmax_t)va_arg(ap, unsigned long);
	else if (IS_UNSIGN(format) && format[-1] == 'j')
		uholder = (uintmax_t)va_arg(ap, uintmax_t);
	else if (format[-1] == 'z')
		uholder = (uintmax_t)va_arg(ap, size_t);
	else
		uholder = (uintmax_t)va_arg(ap, unsigned int);
	tree->zero = (uholder == 0) ? (1) : (0);
	precision(format, ap, tree);
	fubase(uholder, base, tree->c, tree);
}
