/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 14:40:38 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void				help_me(t_flags *f)
{
	f->a = f->a_fin;
	f->b = f->b_fin;
	f->c = f->c_fin;
	f->d = f->d_fin;
}

void				md5_hash(t_flags *f)
{
	uint32_t		i;
	uint32_t		ff;
	uint32_t		g;

	i = 0;
	help_me(f);
	while (i < 64)
	{
		ff = (i <= 15) ? ((f->b & f->c) | ((~f->b) & f->d)) : (ff);
		g = (i <= 15) ? (i) : (g);
		ff = (i >= 16 && i <= 31) ? ((f->d & f->b) | ((~f->d) & f->c)) : (ff);
		g = (i >= 16 && i <= 31) ? ((5 * i + 1) % 16) : (g);
		ff = (i >= 32 && i <= 47) ? (f->b ^ f->c ^ f->d) : (ff);
		g = (i >= 32 && i <= 47) ? ((3 * i + 5) % 16) : (g);
		ff = (i >= 48 && i <= 63) ? (f->c ^ (f->b | (~f->d))) : (ff);
		g = (i >= 48 && i <= 63) ? ((7 * i) % 16) : (g);
		ff = ff + f->a + f->kk[i] + f->mm[g];
		f->a = f->d;
		f->d = f->c;
		f->c = f->b;
		f->b = f->b + left_rotate(ff, f->s[i]);
		i++;
	}
}

void				help_me2(t_flags *f)
{
	f->a_fin += f->a;
	f->b_fin += f->b;
	f->c_fin += f->c;
	f->d_fin += f->d;
}

void				help_me3(t_flags *f)
{
	initi(f);
	f->s = ft_make_s();
	f->kk = ft_make_k();
	f->b_ind = 0;
	f->fd = (f->st) ? (uint32_t)open("./del", O_RDONLY) : (f->fd);
}

void				ft_md5(t_flags *f)
{
	char			buf[130];
	char			*catch;

	help_me3(f);
	while (64 == (f->ret = read(f->fd, buf, 64)))
	{
		buf[f->ret] = '\0';
		(f->fd == 0 && !f->is_ne) ? (ft_printf("%s", buf)) : (0);
		f->mm = (uint32_t*)buf;
		md5_hash(f);
		help_me2(f);
		f->orig_len += 512;
	}
	buf[f->ret] = '\0';
	(f->ret > 0) ? (ft_pad(buf, f)) : (0);
	while (f->i < f->ret)
	{
		f->mm = (uint32_t*)&buf[f->i];
		md5_hash(f);
		help_me2(f);
		f->i += 64;
	}
	catch = append(f);
	ft_putmd5(catch, f);
}
