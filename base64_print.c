/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/02 22:57:59 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void				putstr_nonline(char *hold)
{
	int				i;

	i = 0;
	while (hold[i] != '\0')
	{
		write(1, &hold[i], 1);
		i++;
	}
}

void				print_decode64(unsigned int x, int old_i, t_flags *f)
{
	char			*y;
	int				i;

	x >>= 8;
	y = (char*)&x;
	i = old_i - 2;
	f->dec_fd = (f->dec_fd == 0) ? (1) : (f->dec_fd);
	while (i >= 0)
	{
		write(f->dec_fd, &y[i], 1);
		i--;
	}
}

char				*getchar_64(char *buf)
{
	char			x[64];
	int				i;
	unsigned int	*a;
	char			*ret;
	unsigned int	temp;

	assign_base64(x);
	i = 0;
	temp = 0;
	ret = (char*)malloc(sizeof(char) * 4);
	a = (unsigned int*)buf;
	a[0] = reverse_bits(a[0]);
	reverse_four_bytes((char*)a);
	while (a[0])
	{
		temp = a[0] % 64;
		temp = reverse_bits(temp);
		temp >>= 26;
		ret[i++] = x[temp];
		a[0] /= 64;
	}
	while (i < 4)
		ret[i++] = '=';
	ret[4] = '\0';
	return (ret);
}

unsigned char		find_index(char buf)
{
	char			s[64];
	unsigned char	i;

	assign_base64(s);
	i = 0;
	while (i < 64)
	{
		if (s[i] == buf)
			return (i);
		i++;
	}
	return (0);
}

void				unpack_base64(t_flags *f)
{
	remove("./del2");
	f->dec_fd = (uint32_t)open("./del2", O_RDWR | O_CREAT, 00777);
	f->decode = 1;
	decode_base64(f);
	f->fd = f->dec_fd;
	close(f->fd);
	f->fd = open("./del2", O_RDWR);
}
