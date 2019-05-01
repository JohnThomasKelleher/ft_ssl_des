/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:34:01 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/02 23:26:22 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			precwidth(int many, t_ap *tree, int prec)
{
	while (many > 0)
	{
		tree->ret += ((tree->z_pad && !tree->left && (tree->prec == 10000))
			|| prec) ? (write(1, "0", 1)) : (write(1, " ", 1));
		many--;
	}
}

char			*ft_spad(char *s, t_ap *tree)
{
	char		*delet;

	tree->prec = (tree->prec > (int)ft_strlen(s)) ?
		(ft_strlen(s)) : (tree->prec);
	tree->prec = (tree->prec < 0) ? (10000) : (tree->prec);
	tree->width -= (tree->prec > 0) ? (tree->prec) : (0);
	delet = ft_strsub(s, 0, tree->prec);
	tree->ret += (tree->left && !(tree->zero && tree->dot)) ?
		(bt_putstr_fd(delet, tree)) : (0);
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
	tree->ret += (!tree->left && !(tree->zero && tree->dot))
		? (bt_putstr_fd(delet, tree)) : (0);
	free(delet);
	return (NULL);
}

char			*ft_padder(char *s, t_ap *tree)
{
	tree->len += (ft_strlen(s));
	tree->prec = ((tree->prec >= (int)ft_strlen(s)) && (tree->prec > 0))
		? (tree->prec) : (10000);
	tree->prec -= (tree->prec == 10000) ? (0) : (bt_strlen(s, tree, 1));
	tree->width -= (tree->prec == 10000) ? (bt_strlen(s, tree, 0))
		: (tree->prec + bt_strlen(s, tree, 0));
	tree->width += (FT_PAD2(tree)) ? (0) : (1);
	tree->width -= (SINGLESPACE(tree)) ? (1) : (0);
	tree->ret += (SINGLESPACE(tree)) ? (write(1, " ", 1)) : (0);
	(!tree->left && !tree->z_pad) ? (precwidth(tree->width, tree, 0)) : (0);
	tree->ret += (OX(tree) && IS_LOW(tree->c[0])) ? (write(1, "0x", 2)) : (0);
	tree->ret += (OX(tree) && !IS_LOW(tree->c[0])) ? (write(1, "0X", 2)) : (0);
	tree->ret += (O(tree) && HASH(tree)) ? (write(1, "0", 1)) : (0);
	tree->prec -= (O(tree) && HASH(tree) && tree->prec != 10000) ? (1) : (0);
	tree->ret += ((tree->plus == 1) && (s[0] != '-') && (PLUS(tree)))
		? (write(1, "+", 1)) : (0);
	tree->ret += (s[0] == '-') ? (write(1, "-", 1)) : (0);
	s += (s[0] == '-') ? (1) : (0);
	(tree->z_pad && !tree->left) ? (precwidth(tree->width, tree, 0)) : (0);
	(tree->prec != 10000) ? (precwidth(tree->prec, tree, 1)) : (0);
	tree->ret += (!FT_PAD1(tree)) ?
		(bt_putstr_fd(s, tree)) : (0);
	(tree->left) ? (precwidth(tree->width, tree, 0)) : (0);
	return (NULL);
}

char			*ft_fpad(char *s, t_ap *tree)
{
	tree->width = (tree->whold - tree->len - 2);
	tree->len += (int)ft_strlen(s);
	tree->prec -= ft_strlen(s);
	s[0] = (tree->prec < 0) ? ('\0') : (s[0]);
	s += (s[0] == '-') ? (1) : (0);
	tree->ret += bt_putstr_fd(s, tree);
	precwidth(tree->prec, tree, 1);
	(tree->left) ? (precwidth(tree->width, tree, 0)) : (0);
	return (NULL);
}
