/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/15 21:41:28 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

char			*append(t_flags *f)
{
	uint32_t	*hold;
	int			i;

	i = 0;
	hold = malloc(sizeof(uint32_t) * 4);
	hold[0] = f->a_fin;
	hold[1] = f->b_fin;
	hold[2] = f->c_fin;
	hold[3] = f->d_fin;
	return ((char*)hold);
}

char			*sha_append(t_flags *f)
{
	uint32_t	*ret;

	ret = malloc(sizeof(uint32_t) * 16);
	ret[0] = (TWO_FIFTY(f->det)) ? (f->h_fin) : (f->h7);
	ret[1] = (TWO_FIFTY(f->det)) ? (f->g_fin) : (f->h7 >> 32);
	ret[2] = (TWO_FIFTY(f->det)) ? (f->f_fin) : (f->h6);
	ret[3] = (TWO_FIFTY(f->det)) ? (f->e_fin) : (f->h6 >> 32);
	ret[4] = (TWO_FIFTY(f->det)) ? (f->d_fin) : (f->h5);
	ret[5] = (TWO_FIFTY(f->det)) ? (f->c_fin) : (f->h5 >> 32);
	ret[6] = (TWO_FIFTY(f->det)) ? (f->b_fin) : (f->h4);
	ret[7] = (TWO_FIFTY(f->det)) ? (f->a_fin) : (f->h4 >> 32);
	ret[8] = f->h3;
	ret[9] = (f->h3 >> 32);
	ret[10] = f->h2;
	ret[11] = (f->h2 >> 32);
	ret[12] = f->h1;
	ret[13] = (f->h1 >> 32);
	ret[14] = f->h0;
	ret[15] = (f->h0 >> 32);
	return ((char*)ret);
}
