/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:12:22 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 14:12:00 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int				count_usize(uintmax_t n)
{
	int			i;

	i = 1;
	while (n /= 2)
		i++;
	return (i);
}

int				count_size(intmax_t n)
{
	int			i;

	i = 1;
	while (n /= 2)
		i++;
	return (i);
}

int				precision(char *format, va_list ap, t_ap *tree)
{
	tree->prec = 10000;
	tree->width = 0;
	while (ISDIGIT(format[-1]) || PREC1(format))
		format--;
	(format[0] == '*') ? (tree->width = va_arg(ap, int)) : (0);
	tree->left = (tree->width < 0) ? (1) : (tree->left);
	tree->width = (tree->width < 0) ? (-tree->width) : (tree->width);
	format += (format[0] == '*') ? (1) : (0);
	tree->z_pad = (format[0] == '0' && format[1] != '.') ? (1) : (tree->z_pad);
	tree->prec = (format[0] == '.') ? (ft_atoi(&format[1])) : (tree->prec);
	tree->width = (ISDIGIT(format[0])) ? (ft_atoi(&format[0])) : (tree->width);
	format += (ISDIGIT(format[0])) ? (1) : (0);
	(format[0] == '*') ? (tree->width = va_arg(ap, int)) : (0);
	while (tree->dot && format[0] != '.')
		format++;
	tree->prec = (format[1] == '*' && tree->dot) ? (va_arg(ap, int))
		: (tree->prec);
	tree->prec = (IS_TYPE(format[1]) && tree->dot) ? (0)
		: (tree->prec);
	tree->prec = (ISDIGIT(format[1]) && tree->dot) ? (ft_atoi(&format[1]))
		: (tree->prec);
	tree->width -= ((tree->hash && X(tree)) || tree->c[0] == 'p') ? (2) : (0);
	tree->width -= ((O(tree) && tree->hash)) ? (1) : (0);
	return (0);
}

int				bt_putwstr(wchar_t *s, t_ap *tree)
{
	int			i;
	int			len;

	i = 0;
	len = 0;
	if (tree->c[0] == 'c' || tree->c[0] == 'C')
		return (put_wc(s[0]));
	while (s[i] && i < tree->prec && len < tree->prec)
	{
		len += put_wc(s[i]);
		i++;
	}
	return (len);
}

int				ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	void		(*p[126]) (va_list ap, char *format, t_ap *tree);
	int			i;
	t_ap		*tree;

	if (!(tree = (t_ap*)ft_memalloc(sizeof(t_ap) * 3)))
		return (0);
	i = ass_f(p, tree);
	va_start(ap, format);
	while (format[i] != '\0')
		if (format[i] == '%')
		{
			i++;
			while (PRINTF1(format))
				flags((char*)&format[i++], tree);
			tree->c = (char*)&format[i];
			p[(int)format[i]](ap, (char*)&format[i], tree);
			i += (PRINTF2(format)) ? (zs(tree, i)) : ((zs(tree, i) + 1));
		}
		else
			tree->ret += write(1, &format[i++], 1);
	va_end(ap);
	i = tree->ret;
	free(tree);
	return (i);
}
