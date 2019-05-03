/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 00:57:02 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 01:30:17 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void			other_set_hex(t_flags *f, char *a)
{
	uint64_t	*ret;

	flip_buf(a);
	ret = (uint64_t*)a;
	f->orig_salt = ret[0];
}

int				cmp_salt(char *buf, char *salt)
{
	int			i;

	i = 0;
	while (buf[i] != '\0' && salt[i] != '\0')
	{
		if (buf[i] != salt[i])
			return (1);
		i++;
	}
	if (buf[i] != salt[i])
		return (1);
	return (0);
}

void			read_salt(t_flags *f)
{
	static char	salt[9] = { 'S', 'a', 'l', 't', 'e', 'd', '_', '_' };
	char		buf[9];

	(read(f->fd, buf, 8));
	cmp_salt(buf, salt);
	(read(f->fd, buf, 8));
	other_set_hex(f, buf);
}

void			handle_des(t_flags *f, char **a)
{
	int			hold_fd;

	hold_fd = help_handle_des(f, a);
	while (a[f->i])
	{
		if (a[f->i][0] == '-')
			f->op[(int)(a[f->i][1])](f, a);
		optns(f, a);
		f->i++;
	}
	if (f->p && !f->decrypt)
		write_salt(f);
	f->fd = (f->fd > 0) ? (f->fd) : (0);
	(f->decrypt && f->a_op) ? (unpack_base64(f)) : (0);
	if (f->p && f->decrypt)
		read_salt(f);
	if (f->p && ((hold_fd = f->fd) || !(hold_fd)))
	{
		handle_pass(f, a);
		f->fd = hold_fd;
	}
	(f->alg) ? (f->alg(f)) : (0);
	remove("./del");
	remove("./del2");
	remove("./del3");
}

void			handle_shit(char *buf, t_flags *f)
{
	uint64_t	*hold;

	hold = (uint64_t*)buf;
	flip_buf(buf);
	f->pt_carry = (f->first) ? (f->x) : (f->prev);
	f->prev = hold[0];
	hold[0] ^= (f->ecb || f->decrypt) ? (0) : (f->x);
	f->first = 0;
}
