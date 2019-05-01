/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beurocrat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:21:49 by jkellehe          #+#    #+#             */
/*   Updated: 2018/11/29 12:52:02 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int			zs(t_ap *tree, int i)
{
	tree->rd = 0;
	i += 0;
	tree->dot = 0;
	tree->preast = 0;
	tree->posast = 0;
	tree->fd = 1;
	tree->decimal = 0;
	tree->zero = 0;
	tree->prec = 0;
	tree->left = 0;
	tree->percent = 0;
	tree->l = 0;
	tree->ll = 0;
	tree->fd = 1;
	tree->decimal = 0;
	tree->hash = 0;
	tree->zero = 0;
	tree->z_pad = 0;
	return ((tree->dot = 0));
}

void		oh(va_list ap, char *format, t_ap *tree)
{
	ap += 0;
	format += 0;
	tree->ret = -1;
}

void		null(void (**p) (va_list ap, char *format, t_ap *tree), t_ap *tree)
{
	int		i;

	i = 0;
	tree->ret = 0;
	while (i <= 126)
	{
		p[i] = non;
		i++;
	}
}

int			ass_f(void (**p) (va_list ap, char *format, t_ap *tree), t_ap *tree)
{
	null(p, tree);
	p['p'] = addy;
	p['U'] = udigit;
	p['u'] = udigit;
	p['O'] = udigit;
	p['o'] = udigit;
	p['b'] = digit;
	p['X'] = udigit;
	p['x'] = udigit;
	p['l'] = digit;
	p['d'] = digit;
	p['D'] = big_digit;
	p['i'] = digit;
	p['s'] = str;
	p['S'] = str;
	p['C'] = wchar;
	p['c'] = character;
	p['%'] = percent;
	p['f'] = floot;
	p['F'] = floot;
	p['a'] = floot;
	p['A'] = floot;
	p['}'] = non;
	return (zs(tree, 1));
}

void		flags(char *c, t_ap *tree)
{
	tree->preast = (*c == '*' && !tree->dot) ? (1) : (tree->preast);
	tree->left = (*c == '-') ? (1) : (tree->left);
	tree->l = (*c == 'l') ? (1) : (tree->l);
	tree->ll = (*c == 'l' && c[-1] == 'l') ? (1) : (tree->ll);
	tree->hash = (*c == '#') ? (1) : (tree->hash);
	tree->dot = (*c == '.') ? (1) : (tree->dot);
	tree->plus = (*c == '+') ? (1) : (tree->plus);
	tree->space = (*c == ' ') ? (1) : (tree->space);
	tree->z_pad = (*c == '0' && c[-1] == '%') ? (1) : (tree->z_pad);
}
