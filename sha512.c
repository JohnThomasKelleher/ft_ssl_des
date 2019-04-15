/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   512sha.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/15 21:25:24 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

uint64_t		rr_64(uint64_t w, uint64_t r)
{
	return (((w >> r) | (w << (64 - r))));
}

void			sha512_hash(t_flags *f)
{
	int			i;

	i = 16;
	while (i < 80)
	{
		f->s0 = (rr_64(f->ww[(i - 15)], 1) ^ rr_64(f->ww[(i - 15)], 8)
				^ (f->ww[(i - 15)] >> 7));
		f->s1 = (rr_64(f->ww[(i - 2)], 19) ^ rr_64(f->ww[(i - 2)], 61)
				^ (f->ww[(i - 2)] >> 6));
		f->ww[i] = f->ww[(i - 16)] + f->s0 + f->ww[(i - 7)] + f->s1;
		i++;
	}
	i = sha_init_abc(f);
	while (i < 80)
	{
		f->s1 = (rr_64(f->five, 14) ^ rr_64(f->five, 18) ^ rr_64(f->five, 41));
		f->cha = ((f->five & f->six) ^ ((~f->five) & f->seven));
		f->t1 = f->eight + f->s1 + f->cha + f->k[i] + f->ww[i];
		f->s0 = (rr_64(f->one, 28) ^ rr_64(f->one, 34) ^ rr_64(f->one, 39));
		f->mj = ((f->one & f->two) ^ (f->one & f->three) ^ (f->two & f->three));
		f->t2 = f->s0 + f->mj;
		i += sub_hash(f);
	}
	accumulate(f);
}

void			sha_512(t_flags *f)
{
	uint64_t	w[80];
	char		buf[257];
	uint64_t	k[80];

	f->b_ind = 1;
	f->ww = (uint64_t*)z_ero((uint32_t*)w, f);
	f->k = sha_make_k(k, f);
	f->fd = (f->st) ? (uint32_t)open("./del", O_RDONLY) : (f->fd);
	while (128 == (f->ret = read(f->fd, buf, 128)))
	{
		(f->fd == 0 && !f->is_ne) ? (ft_printf("%s", buf)) : (0);
		sha_copy((char*)w, buf, f);
		sha512_hash(f);
		f->orig_len += 1024;
		f->file += (f->file) ? (128) : (0);
	}
	if (f->ret > 0)
		ft_64pad(buf, f);
	while (f->i < f->ret)
	{
		sha_copy((char*)w, &buf[f->i], f);
		f->i += 128;
		sha512_hash(f);
	}
	print256(sha_append(f), f);
}
