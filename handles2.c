/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 01:32:14 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 01:33:58 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void						handle_flags(t_flags *f, char **a)
{
	if (a[f->i][1] == 'a')
		f->a_op = 1;
	if (a[f->i][1] == 'p')
	{
		f->p = 1;
		f->password = a[(f->i + 1)];
	}
	if (a[f->i][1] == 'd')
		f->decrypt = 1;
}

void						handle_file(t_flags *f, char **a)
{
	if (0 > (f->fd = open(a[(f->i + 1)], O_RDONLY)))
	{
		ft_printf("sorry, no file there\n");
		return ;
	}
}

void						write_salt(t_flags *f)
{
	static char				buf[9] = { 'S', 'a', 'l', 't', 'e', 'd', '_', '_' };
	uint64_t				*b;
	uint64_t				hold;

	f->orig_len_des = 0;
	f->flush = 0;
	hold = f->x;
	b = (uint64_t*)buf;
	flip_buf(buf);
	f->x = b[0];
	(f->a_op) ? (print_cipherb64(f, 0)) : (print_cipher(f));
	f->x = f->orig_salt;
	(f->a_op) ? (print_cipherb64(f, 0)) : (print_cipher(f));
	f->x = hold;
	f->orig_len_des = 20;
}

int							help_handle_des(t_flags *f, char **a)
{
	f->is_iv = 0;
	f->fd_out = 1;
	f->a_op = 0;
	optns(f, a);
	f->i++;
	return (0);
}
