/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:05:21 by jkellehe          #+#    #+#             */
/*   Updated: 2018/11/28 18:52:13 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			wchar(va_list ap, char *format, t_ap *tree)
{
	wchar_t		c;

	precision(format, ap, tree);
	c = va_arg(ap, wchar_t);
	tree->width--;
	tree->ret += ((tree->width > 0) && !tree->left) ?
		(bt_putchar(' ', tree->width)) : (0);
	ft_wpad(&c, tree);
	tree->ret += ((tree->width > 0) && tree->left) ?
		(bt_putchar(' ', tree->width)) : (0);
}

void			character(va_list ap, char *format, t_ap *tree)
{
	char		c;

	if (format[-1] == 'l')
	{
		wchar(ap, format, tree);
		return ;
	}
	precision(format, ap, tree);
	tree->ret += ((--tree->width > 0) && !tree->left && !tree->z_pad) ?
		(bt_putchar(' ', tree->width)) : (0);
	tree->ret += ((tree->width > 0) && !tree->left && tree->z_pad) ?
		(bt_putchar('0', tree->width)) : (0);
	c = (char)va_arg(ap, int);
	tree->ret += write(1, &c, 1);
	tree->ret += ((tree->width > 0) && tree->left && !tree->z_pad) ?
		(bt_putchar(' ', tree->width)) : (0);
	tree->ret += ((tree->width > 0) && tree->left && tree->z_pad) ?
		(bt_putchar('0', tree->width)) : (0);
}

void			percent(va_list ap, char *format, t_ap *tree)
{
	ap += 0;
	precision(format, ap, tree);
	tree->width--;
	while (((tree->width) > 0) && !(tree->left))
	{
		tree->ret += (tree->z_pad) ? (write(1, "0", 1)) : (write(1, " ", 1));
		tree->width--;
	}
	write(1, "%", 1);
	tree->ret++;
	while (((tree->width) > 0) && (tree->left))
	{
		tree->ret += (tree->z_pad) ? (write(1, "0", 1)) : (write(1, " ", 1));
		tree->width--;
	}
}

void			addy(va_list ap, char *format, t_ap *tree)
{
	char		*yeah;
	char		*hold;

	precision(format, ap, tree);
	yeah = va_arg(ap, char*);
	tree->zero = (yeah == NULL) ? (1) : (0);
	tree->hash = 1;
	if (!yeah)
	{
		hold = (char*)malloc(sizeof(char) * 2);
		hold[0] = '0';
		hold[1] = '\0';
	}
	else
		hold = ft_maxtoa_base((intmax_t)yeah, 16, format);
	ft_padder(hold, tree);
	free(hold);
}

void			non(va_list ap, char *format, t_ap *tree)
{
	char		*hold;
	int			prec;

	prec = precision(format, ap, tree);
	hold = (char*)malloc(sizeof(char));
	if (*format == 0 && format[-1] == '%')
		hold += 0;
	else if (*format == 10)
	{
		ft_strncpy(hold, format, 1);
		ft_putstr_fd_prec(hold, tree);
	}
	else
	{
		ft_strncpy(hold, tree->c, 1);
		ft_putstr_fd_prec(hold, tree);
	}
	free(hold);
	return ;
}
