/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:15:55 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 02:17:27 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void		dec_each_block(t_flags *f, char *buf, char *buf2)
{
	handle_shit(buf, f);
	buf[f->ret] = '\0';
	f->file = buf;
	initial_perm(f, 0, 0);
	ft_16_rounds(f);
	final_perm(f, 0, 0);
	if (!f->ecb)
	{
		f->x ^= f->pt_carry;
	}
	(print_cipher(f));
	buf2tobuf(buf, buf2);
	f->ret = f->ret2;
}

void		des_each_block(t_flags *f, char *buf)
{
	handle_shit(buf, f);
	buf[f->ret] = '\0';
	f->file = buf;
	initial_perm(f, 0, 0);
	ft_16_rounds(f);
	final_perm(f, 0, 0);
	(f->a_op && !f->decrypt) ? (print_cipherb64(f, 0)) : (print_cipher(f));
}

void		des_each_block2(t_flags *f, char *buf)
{
	f->file = buf;
	pkcs7_pad(f);
	handle_shit(buf, f);
	initial_perm(f, 0, 0);
	ft_16_rounds(f);
	final_perm(f, 0, 0);
	f->flush = 1;
	(f->a_op) ? (print_cipherb64(f, 0)) : (print_cipher(f));
}

void		dec_each_block2(t_flags *f, char *buf, char *buf2)
{
	buf2 += 0;
	handle_shit(buf, f);
	buf[f->ret] = '\0';
	f->file = buf;
	initial_perm(f, 0, 0);
	ft_16_rounds(f);
	final_perm(f, 0, 0);
	if (!f->ecb)
	{
		f->x ^= f->pt_carry;
	}
}

void		dec_each_block3(t_flags *f, char *buf, char *buf2)
{
	buf += 0;
	f->flush = 1;
	handle_shit(buf2, f);
	buf2[f->ret2] = '\0';
	f->file = buf2;
	initial_perm(f, 0, 0);
	ft_16_rounds(f);
	final_perm(f, 0, 0);
	if (!f->ecb)
	{
		f->x ^= f->pt_carry;
	}
}
