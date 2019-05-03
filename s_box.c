/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_box.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:54:22 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 02:54:54 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void				s_boxes(t_flags *f)
{
	static uint8_t	(*boxes[8]) (uint8_t) = { s1, s2, s3, s4, s5, s6, s7, s8 };
	int				i;
	uint8_t			in;

	i = 7;
	in = 0;
	while (i > -1)
	{
		in = (f->ex_r % 64);
		f->ex_r /= 64;
		in = boxes[i](in);
		f->f_hold <<= 4;
		f->f_hold += in;
		i--;
	}
	reverse_half_bytes(f);
}
