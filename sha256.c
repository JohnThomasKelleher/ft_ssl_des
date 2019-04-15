/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   256sha.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 16:48:36 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void			sha256_hash(t_flags *f)
{
	int			i;
	uint32_t	s0;
	uint32_t	s1;

	i = 15;
	while (++i < 64)
	{
		s0 = (rr(f->w[(i - 15)], 7) ^
				rr(f->w[(i - 15)], 18) ^ (f->w[(i - 15)] >> 3));
		s1 = (rr(f->w[(i - 2)], 17) ^
				rr(f->w[(i - 2)], 19) ^ (f->w[(i - 2)] >> 10));
		f->w[i] = f->w[(i - 16)] + s0 + f->w[(i - 7)] + s1;
	}
	i = sha_init_abc(f) - 1;
	while (++i < 64)
	{
		s1 = (rr(f->e, 6) ^ rr(f->e, 11) ^ rr(f->e, 25));
		f->ch = ((f->e & f->f) ^ ((~f->e) & f->g));
		f->temp1 = f->h + s1 + f->ch + f->k[i] + f->w[i];
		s0 = (rr(f->a, 2) ^ rr(f->a, 13) ^ rr(f->a, 22));
		f->maj = ((f->a & f->b) ^ (f->a & f->c) ^ (f->b & f->c));
		f->temp2 = s0 + f->maj;
		sub_hash(f);
	}
	accumulate(f);
}

void			sha_256(t_flags *f)
{
	uint32_t	w[64];
	char		buf[130];
	uint64_t	k[80];

	f->b_ind = 1;
	f->w = z_ero(w, f);
	f->k = sha_make_k(k, f);
	f->fd = (f->st) ? (uint32_t)open("./del", O_RDONLY) : (f->fd);
	while (64 == (f->ret = read(f->fd, buf, 64)))
	{
		(f->fd == 0 && !f->is_ne) ? (ft_printf("%s", buf)) : (0);
		sha_copy((char*)w, buf, f);
		sha256_hash(f);
		f->orig_len += 512;
	}
	if (f->ret > 0 || (f->file && f->ret))
		ft_pad(buf, f);
	while (f->i < f->ret)
	{
		sha_copy((char*)w, &buf[f->i], f);
		f->i += 64;
		sha256_hash(f);
	}
	print256(sha_append(f), f);
}
