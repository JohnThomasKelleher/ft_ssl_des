/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_printers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:33:59 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 00:40:47 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void				base64_out(char *b, t_flags *f, int j)
{
	uint32_t		*c;
	int				end;
	char			out;
	int				i;
	char			s[64];

	assign_base64(s);
	i = 0;
	end = 3;
	reverse_four_bytes(b);
	c = (uint32_t*)b;
	if (f->flush)
	{
		end -= j;
	}
	while (i <= end)
	{
		out = ((c[0] >> (26 - 6 * i)) & 0x3f);
		if (f->orig_len_des && f->orig_len_des % 64 == 0)
			write(f->fd_out, "\n", 1);
		f->orig_len_des += write(f->fd_out, &s[(int)out], 1);
		i++;
	}
	while (i++ <= 3)
		f->orig_len_des += write(f->fd_out, "=", 1);
}

void				print_cipherb64(t_flags *f, int i)
{
	static char		b[4];
	int				place_in_x;
	static int		place_in_b;
	uint32_t		*x;

	place_in_x = 0;
	x = (uint32_t*)b;
	while (place_in_x <= 7)
	{
		b[place_in_b++] = (f->x >> (56 - 8 * place_in_x++)) & 0xff;
		if (place_in_b == 3)
		{
			place_in_b = 0;
			b[3] = '\0';
			base64_out(b, f, 0);
		}
	}
	if (f->flush && place_in_b && (i = -1))
	{
		while (place_in_b <= 3 && ((i += 1) || (!i)))
			b[place_in_b++] = 0;
		base64_out(b, f, (i));
	}
	if (f->flush)
		write(f->fd_out, "\n", 1);
}

int					print_cipher(t_flags *f)
{
	int				i;
	uint64_t		x_val;
	char			*x;
	int				end;

	i = 0;
	end = 8;
	x_val = f->x;
	x = (char*)&x_val;
	if (f->decrypt && f->flush)
	{
		(end = (8 - x[0]));
	}
	flip_buf(x);
	while (i < end)
	{
		write(f->fd_out, &x[i], 1);
		i++;
	}
	return (0);
}
