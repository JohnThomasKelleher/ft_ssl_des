/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 14:41:59 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

uint32_t	left_rotate(uint32_t n, uint32_t d)
{
	return (n << d) | (n >> (32 - d));
}

void		ft_err(t_flags *f)
{
	f->i += 0;
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
}
