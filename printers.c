/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 14:45:26 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void			ft_putmd5(char *catch, t_flags *f)
{
	int			i;

	i = 0;
	if (f->st)
		(f->r || f->q) ? (0) : (ft_printf("MD5 (\"%s\") = ", f->name));
	else if (!f->p && !f->never)
		(f->r || f->q) ? (0) : (ft_printf("MD5 (%s) = ", f->name));
	while (i < 16)
	{
		ft_printf("%02hhx", (unsigned char)catch[i]);
		i++;
	}
	if (f->st)
		(f->r && !f->q) ? (ft_printf(" \"%s\"", f->name)) : (0);
	else if (!f->p)
		(f->r && !f->q) ? (ft_printf(" %s", f->name)) : (0);
	ft_printf("\n");
}

void			print256(char *p, t_flags *f)
{
	int			i;
	int			end;

	if (f->st)
		(f->r || f->q) ? (0) : (ft_printf("%s (\"%s\") = ", f->algy, f->name));
	else if (!f->p && !f->never)
		(f->r || f->q) ? (0) : (ft_printf("%s (%s) = ", f->algy, f->name));
	i = (TWO_FIFTY(f->det)) ? (31) : (63);
	end = (f->det == 2) ? (4) : (0);
	end = (f->det == 4) ? (16) : (end);
	while (i >= end)
	{
		ft_printf("%02hhx", p[i]);
		i--;
	}
	if (f->st)
		(f->r && !f->q) ? (ft_printf(" \"%s\"", f->name)) : (0);
	else if (!f->p)
		(f->r && !f->q) ? (ft_printf(" %s", f->name)) : (0);
	ft_printf("\n");
}
