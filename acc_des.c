/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acc_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:04:39 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/02 23:04:44 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

uint32_t		lr_28(uint32_t n, uint32_t d)
{
	uint32_t	hold;
	uint32_t	res;

	res = 0;
	hold = n;
	res = ((n << d));
	res &= 0xFFFFFFF;
	res |= (n >> (28 - d));
	return (res);
}

void			ass_dig(int *dig)
{
	dig['0'] = 0;
	dig['1'] = 1;
	dig['2'] = 2;
	dig['3'] = 3;
	dig['4'] = 4;
	dig['5'] = 5;
	dig['6'] = 6;
	dig['7'] = 7;
	dig['8'] = 8;
	dig['9'] = 9;
	dig['a'] = 10;
	dig['A'] = 10;
	dig['b'] = 11;
	dig['B'] = 11;
	dig['c'] = 12;
	dig['C'] = 12;
	dig['d'] = 13;
	dig['D'] = 13;
	dig['e'] = 14;
	dig['E'] = 14;
	dig['f'] = 15;
	dig['F'] = 15;
}
