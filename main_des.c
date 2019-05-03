/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_des.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:10:42 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 02:13:59 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void				ft_16_rounds(t_flags *f)
{
	int				i;

	i = 0;
	while (i < 16)
	{
		expansion_des(f);
		if (f->decrypt)
			f->ex_r ^= f->keys[(15 - i)];
		else
			f->ex_r ^= f->keys[i];
		s_boxes(f);
		str8_d_box(f);
		f->l ^= f->f_hold;
		if (i != 15)
			swap_lr(f);
		i++;
	}
}

void				flip_buf(char *buf)
{
	char			hold;

	hold = buf[0];
	buf[0] = buf[7];
	buf[7] = hold;
	hold = buf[1];
	buf[1] = buf[6];
	buf[6] = hold;
	hold = buf[2];
	buf[2] = buf[5];
	buf[5] = hold;
	hold = buf[3];
	buf[3] = buf[4];
	buf[4] = hold;
}

void				ft_des_ecb(t_flags *f)
{
	f->ecb = 1;
	if (!f->decrypt)
		ft_des(f);
	else
		ft_des_decrypt(f);
}

void				ft_des(t_flags *f)
{
	char			buf[9];
	int				i;

	i = 0;
	if (f->decrypt)
	{
		ft_des_decrypt(f);
		return ;
	}
	if (!f->p && !f->ecb && !f->is_iv)
	{
		write(1, "iv undefined\n", 13);
		return ;
	}
	f->keys = (uint64_t*)malloc(sizeof(uint64_t) * 17);
	generate_keys_des(f);
	while (8 == (f->ret = read(f->fd, buf, 8)))
	{
		des_each_block(f, buf);
		i++;
	}
	if (!f->decrypt)
	{
		des_each_block2(f, buf);
	}
}

void				ft_des_decrypt(t_flags *f)
{
	char			buf[9];
	int				i;
	char			buf2[9];

	i = 0;
	f->first = 1;
	f->keys = (uint64_t*)malloc(sizeof(uint64_t) * 17);
	generate_keys_des(f);
	f->flush = 0;
	f->ret = read(f->fd, buf, 8);
	while (8 == (f->ret2 = read(f->fd, buf2, 8)))
	{
		dec_each_block(f, buf, buf2);
		i++;
	}
	if (f->ret2 <= 1 || (f->ret2 == 2 && buf2[0] == '\0' && buf2[1] == '\0'))
		f->flush = 1;
	dec_each_block2(f, buf, buf2);
	(print_cipher(f));
	return ;
	if (f->ret2 > 1 && !(buf2[0] == '\0' && buf2[1] == '\0'))
	{
		dec_each_block3(f, buf, buf2);
		(print_cipher(f));
	}
}
