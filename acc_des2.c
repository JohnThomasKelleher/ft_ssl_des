/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acc_des2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:11:10 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/02 23:11:16 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void					reverse_half_bytes(t_flags *f)
{
	int					i;
	uint32_t			hold;
	uint32_t			other_hold;

	i = 0;
	hold = 0;
	other_hold = 0;
	while (i < 8)
	{
		other_hold = (f->f_hold & 0xF);
		f->f_hold >>= 4;
		hold <<= 4;
		hold += other_hold;
		i++;
	}
	f->f_hold = hold;
}

void					str8_d_box(t_flags *f)
{
	static int			a[32] = {
		15, 6, 19, 20, 28, 11, 27, 16, 0, 14, 22, 25, 4, 17,
		30, 9, 1, 7, 23, 13, 31, 26, 2, 8, 18, 12, 29, 5,
		21, 10, 3, 24
	};
	int					i;
	uint32_t			x;
	uint32_t			rev;

	i = 0;
	rev = 0;
	while (i < 32)
	{
		x = f->f_hold;
		x <<= a[i];
		x >>= 31;
		x <<= (32 - (i) - 1);
		rev |= x;
		i++;
	}
	f->f_hold = rev;
}

void					swap_lr(t_flags *f)
{
	uint32_t			hold;

	hold = f->l;
	f->l = f->ar;
	f->ar = hold;
}

void					buf2tobuf(char *buf, char *buf2)
{
	int					i;

	i = 0;
	while (i < 8)
	{
		buf[i] = buf2[i];
		i++;
	}
}
