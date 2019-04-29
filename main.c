/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 14:39:56 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

t_flags				*help_main(t_flags *f)
{
  //f = malloc(sizeof(t_flags));
	f->never = 1;
	f->is_ne = 0;
	f->p = 0;
	f->st = 0;
	f->i = 0;
	f->orig_len = 0;
	f->file = NULL;
	f->fd = -20;
	f->q = 0;
	f->r = 0;
	f->alg = ft_err;
	f->i = 1;
	f->decode = 0;
	f->ecb = 0;
	f->flush = 0;
	f->orig_salt = 0;
	f->p = 0;
	return (f);
}

int					main(int argc, char **argv)
{
	t_flags			*f;
	char *x;
	char y[2];
	
	x = 0;
	x = NULL;
	x = (char*)malloc(sizeof(char) * 2);

	y[0]+=0;
	argv[argc] = NULL;
	f = malloc(sizeof(t_flags) * 2);
	ass_op(f);
	f->argc = argc;
	if (argc == 1)
	{
		ft_err(f);
		return (1);
	}
	f = help_main(f);
	parse(f, argv);
	return (0);
}
