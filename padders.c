/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/15 23:18:43 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void			l_ind(char *hold, char *buf, t_flags *f)
{
	while ((f->ret % 64) != 0)
	{
		buf[f->ret] = *hold;
		hold++;
		f->ret++;
	}
}

void			b_ind(char *hold, char *buf, t_flags *f)
{
	int			j;
	int			k;

	j = (TWO_FIFTY(f->det)) ? (7) : (15);
	k = 0;
	while ((f->ret % 64) != 0 && (j != 7))
	{
		buf[f->ret] = 0;
		f->ret++;
		k = j;
		j--;
	}
	while (0 <= j)
	{
		buf[f->ret] = hold[j];
		f->ret++;
		j--;
	}
}

void			ft_64pad(char *buf, t_flags *f)
{
	char		*hold;

	(f->fd == 0 && !f->is_ne) ? (ft_printf("%s", buf)) : (0);
	buf = (f->file) ? (ft_strcpy(buf, f->file)) : (buf);
	f->orig_len += (f->ret * 8);
	hold = (char*)&f->orig_len;
	buf[f->ret++] = -128;
	while (f->ret != 112 && f->ret != 240)
	{
		buf[f->ret] = 0;
		f->ret++;
	}
	if (f->b_ind == 1)
		b_ind(hold, buf, f);
	else
		l_ind(hold, buf, f);
}

void			ft_pad(char *buf, t_flags *f)
{
	char		*hold;

	(f->fd == 0 && !f->is_ne) ? (ft_printf("%s", buf)) : (0);
	buf = (f->file) ? (ft_strcpy(buf, f->file)) : (buf);
	f->orig_len += (f->ret * 8);
	hold = (char*)&f->orig_len;
	buf[f->ret++] = -128;
	while (f->ret != 56 && f->ret != 120)
	{
		buf[f->ret] = 0;
		f->ret++;
	}
	if (f->b_ind == 1)
		b_ind(hold, buf, f);
	else
		l_ind(hold, buf, f);
}
