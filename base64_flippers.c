/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/02 23:01:49 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void				assign_base64(char *x)
{
	int				asci;
	int				i;

	i = 0;
	asci = 'A';
	while (asci <= 'Z')
		x[i++] = asci++;
	asci = 'a';
	while (asci <= 'z')
		x[i++] = asci++;
	asci = '0';
	while (asci <= '9')
		x[i++] = asci++;
	x[62] = '+';
	x[63] = '/';
}

unsigned int		reverse_bits(unsigned int x)
{
	int				i;
	unsigned int	a;
	unsigned int	rev;
	unsigned int	hold;

	i = 0;
	rev = 0;
	a = x;
	while (i < 32)
	{
		hold = a;
		hold <<= i;
		hold >>= (31);
		hold <<= i;
		rev |= hold;
		i++;
	}
	return (rev);
}

unsigned char		reverse_bits_char(unsigned char x)
{
	int				i;
	unsigned char	a;
	unsigned char	rev;
	unsigned char	hold;

	rev = 0;
	i = 0;
	a = x;
	while (i < 8)
	{
		hold = a;
		hold <<= i;
		hold >>= 7;
		hold <<= i;
		rev |= hold;
		i++;
	}
	rev >>= 2;
	return (rev);
}

void				reverse_four_bytes(char *x)
{
	unsigned int	h[4];

	h[0] = x[0];
	h[1] = x[1];
	h[2] = x[2];
	x[0] = x[3];
	x[1] = h[2];
	x[2] = h[1];
	x[3] = h[0];
}
