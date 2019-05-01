/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:36:01 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/02 23:44:52 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char			*ft_maxtoa_base(intmax_t n, intmax_t base, char *format)
{
	char		*str;
	int			len;
	intmax_t	tmp;
	char		*digits;
	char		*hold;

	digits = "0123456789ABCDEF";
	if (IS_LOW(format[0]))
		digits = "0123456789abcdef";
	len = count_size(n);
	tmp = n;
	if (n < 0 && ++len)
		tmp *= -1;
	if (!(str = ft_strnew(len)))
		return (NULL);
	str[--len] = digits[ft_abs(tmp % base)];
	while ((tmp = tmp / base))
		str[--len] = digits[ft_abs(tmp % base)];
	if (n < 0)
		str[--len] = '-';
	hold = ft_strdup(&str[len]);
	free(str);
	return (hold);
}

char			*fubase(uintmax_t n, uintmax_t base, char *format, t_ap *tree)
{
	char		str[70];
	int			len;
	uintmax_t	tmp;
	char		*digits;

	digits = "0123456789ABCDEF";
	if (IS_LOW(format[0]))
		digits = "0123456789abcdef";
	len = count_usize(n);
	tmp = n;
	str[len--] = '\0';
	str[len] = digits[tmp % base];
	while ((tmp = tmp / base))
		str[--len] = digits[(tmp % base)];
	ft_putstr_fd_prec(&str[len], tree);
	return (NULL);
}

int				allnine(intmax_t tip)
{
	if (ft_abs(tip % 10) != 9)
		return (0);
	while ((tip /= 10))
	{
		if (ft_abs(tip % 10) != 9)
			return (0);
	}
	return (1);
}

intmax_t		decimals(double holder, float base, t_ap *tree)
{
	intmax_t	i;
	intmax_t	tip;
	double		top;

	i = 0;
	tree->prec = (tree->prec == 10000) ? (6) : (tree->prec);
	tip = (intmax_t)holder;
	top = (double)tip;
	holder -= top;
	while ((i < tree->prec) && i++ < 18)
		holder *= base;
	tip = (intmax_t)holder;
	top = (double)tip;
	holder -= top;
	holder *= (holder < 0) ? (-1) : (1);
	if (((int)(holder * base) % (int)base) >= ((int)base / 2))
	{
		if ((tip == 0 || allnine(tip)) && (tree->rd = 1))
			return (0);
		else if ((tip % 10) != 2)
			tip += (tip > 0) ? (1) : (-1);
	}
	tip *= (tip > 0) ? (1) : (-1);
	return (tip);
}

void			floot(va_list ap, char *format, t_ap *tree)
{
	long double holder;
	intmax_t	temp;

	if (format[-1] == 'L')
		holder = va_arg(ap, long double);
	else
		holder = (long double)va_arg(ap, double);
	precision(format, ap, tree);
	tree->phold = tree->prec;
	temp = (decimals(holder, 10, tree));
	holder = (tree->rd && FLO1(holder)) ? (holder + 1) : (holder);
	holder = (tree->rd && FLO2(holder)) ? (holder - 1) : (holder);
	tree->prec = 10000;
	tree->ret += (holder > -1 && holder < 0) ? (write(1, "-", 1)) : (0);
	tree->whold = tree->width;
	tree->width = (!tree->left) ? (tree->width) : (0);
	ft_padder(ft_maxtoa_base((intmax_t)holder,
		(intmax_t)10, format), tree);
	tree->prec = (FLOOT(tree) || tree->phold == 10000) ? (6) : (tree->phold);
	tree->ret += (tree->prec) ? (write(1, ".", 1)) : (0);
	ft_fpad(ft_maxtoa_base((intmax_t)temp,
		(intmax_t)10, format), tree);
}
