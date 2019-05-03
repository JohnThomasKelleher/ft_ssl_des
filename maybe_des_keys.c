/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maybe_des_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:26:11 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 02:27:26 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void			set_hex(t_flags *f, char **a)
{
	int			dig[124];
	int			j;
	int			i;
	uint64_t	ret;

	j = (f->i + 1);
	i = 0;
	ret = 0;
	ass_dig(dig);
	while (a[j][i] != '\0' && i < 16)
	{
		ret *= 16;
		if (!HEX(a[j][i]))
		{
			f->invalid_key = 1;
			return ;
		}
		ret += dig[(int)a[j][i++]];
	}
	while (i++ < 16)
	{
		ret *= 16;
		ret += 0;
	}
	help_set_hex(f, a, ret);
}

void			generate_keys_des(t_flags *f)
{
	uint32_t	left;
	uint32_t	right;
	int			i;
	uint64_t	hold;
	uint8_t		shift;

	i = 0;
	parity_drop(f);
	left = (f->in_key >> 28);
	right = (f->in_key & 0xfffffff);
	while (i < 16)
	{
		shift = (i == 0 || i == 1 || i == 8 || i == 15) ? (1) : (2);
		left = lr_28(left, shift);
		right = lr_28(right, shift);
		hold = 0;
		hold |= (left);
		hold <<= 28;
		hold |= right;
		hold = comp_dbox(hold);
		f->keys[i] = hold;
		i++;
	}
}
