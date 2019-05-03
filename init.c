/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 01:38:20 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

int				sha_init_abc(t_flags *f)
{
	f->a = f->a_fin;
	f->b = f->b_fin;
	f->c = f->c_fin;
	f->d = f->d_fin;
	f->e = f->e_fin;
	f->f = f->f_fin;
	f->g = f->g_fin;
	f->h = f->h_fin;
	f->one = f->h0;
	f->two = f->h1;
	f->three = f->h2;
	f->four = f->h3;
	f->five = f->h4;
	f->six = f->h5;
	f->seven = f->h6;
	f->eight = f->h7;
	f->a_op = 0;
	f->decrypt = 0;
	f->dec_fd = 1;
	return (0);
}

int				sha_initi(t_flags *f)
{
	f->a_fin = (f->det == 2) ? (0xc1059ed8) : (0x6a09e667);
	f->b_fin = (f->det == 2) ? (0x367cd507) : (0xbb67ae85);
	f->c_fin = (f->det == 2) ? (0x3070dd17) : (0x3c6ef372);
	f->d_fin = (f->det == 2) ? (0xf70e5939) : (0xa54ff53a);
	f->e_fin = (f->det == 2) ? (0xffc00b31) : (0x510e527f);
	f->f_fin = (f->det == 2) ? (0x68581511) : (0x9b05688c);
	f->g_fin = (f->det == 2) ? (0x64f98fa7) : (0x1f83d9ab);
	f->h_fin = (f->det == 2) ? (0xbefa4fa4) : (0x5be0cd19);
	f->h0 = (f->det == 4) ? (0xcbbb9d5dc1059ed8) : (0x6a09e667f3bcc908);
	f->h1 = (f->det == 4) ? (0x629a292a367cd507) : (0xbb67ae8584caa73b);
	f->h2 = (f->det == 4) ? (0x9159015a3070dd17) : (0x3c6ef372fe94f82b);
	f->h3 = (f->det == 4) ? (0x152fecd8f70e5939) : (0xa54ff53a5f1d36f1);
	f->h4 = (f->det == 4) ? (0x67332667ffc00b31) : (0x510e527fade682d1);
	f->h5 = (f->det == 4) ? (0x8eb44a8768581511) : (0x9b05688c2b3e6c1f);
	f->h6 = (f->det == 4) ? (0xdb0c2e0d64f98fa7) : (0x1f83d9abfb41bd6b);
	f->h7 = (f->det == 4) ? (0x47b5481dbefa4fa4) : (0x5be0cd19137e2179);
	return (0);
}

void			initi(t_flags *f)
{
	f->orig_len = 0;
	f->a_fin = 0x67452301;
	f->b_fin = 0xefcdab89;
	f->c_fin = 0x98badcfe;
	f->d_fin = 0x10325476;
	f->a = 0x67452301;
	f->b = 0xefcdab89;
	f->c = 0x98badcfe;
	f->d = 0x10325476;
	f->x_hold = 0;
	f->invalid_key = 0;
}

void			ass_op(t_flags *f)
{
	int			i;

	f->op = malloc(8 * 127);
	i = 0;
	while (i < 127)
		f->op[i++] = invalid_option;
	f->fd_out = 0;
	f->op['o'] = openoutputfile;
	f->op['p'] = handle_flags;
	f->op['q'] = ft_flags;
	f->op['r'] = ft_flags;
	f->op['s'] = set_hex;
	f->op['e'] = handle_flags;
	f->op['d'] = handle_flags;
	f->op['i'] = handle_file;
	f->op['a'] = handle_flags;
	f->op['k'] = set_hex;
	f->op['v'] = set_hex;
}
