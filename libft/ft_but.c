/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_but.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:26:37 by jkellehe          #+#    #+#             */
/*   Updated: 2018/11/29 15:00:01 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int				bt_putstr_fd(char const *s, t_ap *tree)
{
	int			ret;

	tree->len += (int)ft_strlen(s);
	tree->ret += 0;
	ret = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		write(tree->fd, s, 1);
		s++;
		ret++;
	}
	return (ret);
}

int				bt_putchar(char c, int times)
{
	int			count;

	count = times;
	while (times > 0)
	{
		write(1, &c, 1);
		times--;
	}
	return (count);
}

int				bt_strlen(const char *s, t_ap *tree, int prec)
{
	int			i;
	int			len;

	len = 0;
	i = 0;
	while (s[i] != '\0')
		len += ((s[i++] == '-' && prec) || FT_PAD1(tree)) ? (0) : (1);
	len += (tree->plus && !tree->neg && !prec && !FT_PAD1(tree)) ? (1) : (0);
	return (len);
}

intmax_t		ft_abs(intmax_t in)
{
	int			out;

	out = 0;
	if (in < 0)
		return ((out = -1 * in));
	return (in);
}

void			ft_putstr_fd_prec(char *s, t_ap *tree)
{
	if (NUMBERS(tree->c))
	{
		ft_padder(s, tree);
	}
	else
		ft_spad(s, tree);
}
