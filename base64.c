/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/02 22:35:13 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void				handle_b64(t_flags *f, char **a)
{
	while (a[f->i] != '\0')
	{
		if (a[f->i][0] == '-')
			f->op[(int)a[f->i][1]](f, a);
		f->i++;
	}
	if (f->fd <= 0)
		f->fd = 0;
	if (f->decrypt)
		decode_base64(f);
	else
		base64(f);
}

void				rem_whitespace(t_flags *f)
{
	char			buf[1];
	int				fd_hold;

	fd_hold = 0;
	remove("./del3");
	fd_hold = open("./del3", O_RDWR | O_CREAT, 00777);
	while (0 < read(f->fd, buf, 1))
	{
		if (buf[0] != ' ' && buf[0] != 9 && buf[0] != '\n')
			write(fd_hold, &buf[0], 1);
	}
	if (f->fd != 0)
		close(f->fd);
	f->fd = fd_hold;
	close(f->fd);
}

void				decode_base64(t_flags *f)
{
	unsigned int	hold;
	char			buf[5];
	uint8_t			x;
	int				i;

	i = 0;
	rem_whitespace(f);
	f->fd = open("./del3", O_RDWR);
	while (1 < (f->ret = read(f->fd, buf, 4)))
	{
		buf[f->ret] = '\0';
		hold = 0;
		i = f->ret - 1;
		while (i >= 0)
		{
			x = find_index(buf[i]);
			x = reverse_bits_char(x);
			hold <<= 6;
			hold |= x;
			i--;
		}
		hold = reverse_bits(hold);
		print_decode64(hold, f->ret, f);
	}
}

void				base64(t_flags *f)
{
	char			buf[4];
	char			*hold;

	while ((f->ret = read(f->fd, buf, 3)))
	{
		buf[3] = 0;
		buf[2] = (f->ret == 2) ? (0) : (buf[2]);
		buf[1] = (f->ret == 1) ? (0) : (buf[1]);
		hold = getchar_64(buf);
		putstr_nonline(hold);
	}
	write(1, "\n", 1);
}
