/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 02:45:09 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 02:45:14 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

uint64_t			get_salt(void)
{
	uint64_t		*ret;
	int				fd;
	char			buf[8];

	fd = 0;
	ret = (uint64_t*)buf;
	fd = open("/dev/random", O_RDONLY);
	read(fd, buf, 8);
	return (ret[0]);
}

void				ft_the_writer(t_flags *f, char *x, int len)
{
	int				i;

	i = 0;
	while (i < len)
	{
		write(f->fd, &x[i], 1);
		i++;
	}
}

void				ft_pwdin(t_flags *f, char **x, int len)
{
	remove("./del");
	f->never = 0;
	f->st = 1;
	f->st = 1;
	f->fd = (uint32_t)open("./del", O_RDWR | O_CREAT, 00777);
	ft_the_writer(f, x[0], len);
	ft_md5(f);
	f->file = NULL;
	f->st = 0;
	close(f->fd);
	remove("./del");
}

int					concat(char **x, t_flags *f)
{
	char			*hold;
	int				len;
	int				i;
	int				j;

	i = 0;
	j = 0;
	len = ft_strlen(f->password);
	hold = (char*)&f->orig_salt;
	x[0] = (char*)malloc(sizeof(char) * (len + 9));
	while (f->password[i] != '\0')
	{
		x[0][i] = f->password[i];
		i++;
	}
	flip_buf(hold);
	while (j < 8)
	{
		x[0][i] = hold[j];
		j++;
		i++;
	}
	return (i);
}

void				handle_pass(t_flags *f, char **a)
{
	char			**x;
	int				len;

	a += 0;
	x = (char**)malloc(sizeof(char*) * 2);
	initi(f);
	f->s = ft_make_s();
	f->kk = ft_make_k();
	f->b_ind = 0;
	f->orig_salt = (f->orig_salt) ? (f->orig_salt) : (get_salt());
	f->salt = f->orig_salt;
	len = concat(x, f);
	f->orig_len = 0;
	ft_pwdin(f, x, len);
	f->in_key = 0;
	f->in_key += f->b_fin;
	f->in_key <<= 32;
	f->in_key += f->a_fin;
	f->x += f->d_fin;
	f->x <<= 32;
	f->x += f->c_fin;
	flip_buf((char*)&f->x);
	flip_buf((char*)&f->in_key);
	free(x[0]);
	free(x);
}
