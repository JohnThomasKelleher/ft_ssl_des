/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thicc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:31:18 by jkellehe          #+#    #+#             */
/*   Updated: 2018/11/28 21:30:09 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		put_wchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int		put_wc(wchar_t c)
{
	if (c <= 0x7F)
		return (put_wchar(c));
	else if (c <= 0x7FF)
	{
		put_wchar((c >> 6) | 0xC0);
		return (put_wchar((c & 0x3F) | 0x80) * 2);
	}
	else if (c <= 0xFFFF)
	{
		put_wchar(((c >> 12) | 0xE0));
		put_wchar(((c >> 6) & 0x3F) | 0x80);
		return (put_wchar((c & 0x3F) | 0x80) * 3);
	}
	else if (c <= 0x10FFFF)
	{
		put_wchar((c >> 18) | 0xF0);
		put_wchar(((c >> 12) & 0x3F) | 0x80);
		put_wchar(((c >> 6) & 0x3F) | 0x80);
		return (put_wchar((c & 0x3F) | 0x80) * 4);
	}
	return (0);
}

int		ft_wstrlen(wchar_t *wc)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (wc[++i] != 0)
	{
		if (wc[i] <= 0x7F)
			len++;
		else if (wc[i] <= 0x7FF)
			len += 2;
		else if (wc[i] <= 0xFFFF)
			len += 3;
		else if (wc[i] <= 0x10FFFF)
			len += 4;
	}
	return (len);
}

char	*ft_wpad(wchar_t *s, t_ap *tree)
{
	tree->len = ft_wstrlen(s);
	tree->prec = ((tree->prec > tree->len) && tree->prec != 10000) ?
		(tree->len) : (tree->prec);
	tree->width -= (tree->prec >= tree->len) ?
		(tree->len) : (tree->prec);
	tree->ret += (tree->left && !(tree->zero && tree->dot) && THICC(tree->c)) ?
		(bt_putwstr(s, tree)) : (0);
	while (tree->width > 0)
	{
		tree->ret += (tree->z_pad && !tree->left) ?
			(write(1, "0", 1)) : (write(1, " ", 1));
		tree->width--;
	}
	while (tree->prec != 10000 && (tree->prec > 0) && NUMBERS(tree->c))
	{
		tree->ret += ((tree->c[0] != 'x' && tree->c[0] != 'X') || tree->z_pad) ?
			(write(1, "0", 1)) : (write(1, " ", 1));
		tree->prec--;
	}
	tree->ret += (!tree->left && !(tree->zero && tree->dot) && THICC(tree->c))
		? (bt_putwstr(s, tree)) : (0);
	return (NULL);
}
