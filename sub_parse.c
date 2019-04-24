/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 14:46:07 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void		ft_quiet(t_flags *f, char **argv)
{
	int		i;

	i = 0;
	while (argv[i] != NULL)
	{
		f->q = (argv[i][0] == '-' && argv[i][1] == 'q') ? (1) : (f->q);
		i++;
	}
}

void		ft_stdin(t_flags *f, char **argv)
{
  printf("entering stdin\n");
  f->decode = (f->recent_letter == 'd') ? (1) : (0);
	argv += 0;
	f->fd = 0;
	f->never = 0;
	f->i = 0;
	f->p = 1;
	f->alg(f);
	f->p = 0;
}

void		ft_flags(t_flags *f, char **argv)
{
	f->r = (argv[f->i][1] == 'r') ? (1) : (f->r);
	f->q = (argv[f->i][1] == 'q') ? (1) : (f->q);
}

void		ft_writer(t_flags *f, char **argv)
{
	int		i;

	i = 0;
	while (argv[f->i][i] != '\0')
	{
		write(f->fd, &argv[f->i][i], 1);
		i++;
	}
}

void		ft_strin(t_flags *f, char **argv)
{
	remove("./del");
	f->never = 0;
	f->st = 1;
	f->i++;
	f->name = argv[f->i];
	f->st = 1;
	f->fd = (uint32_t)open("./del", O_RDWR | O_CREAT, 00777);
	//if (OLD(f))
	ft_writer(f, argv);
	f->i = 0;
	f->alg(f);
	f->file = NULL;
	f->st = 0;
	f->hold++;
	close(f->fd);
	remove("./del");
}
