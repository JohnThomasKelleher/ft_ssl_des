/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 01:39:05 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 01:39:43 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void						openoutputfile(t_flags *f, char **a)
{
	f->fd_out = (uint32_t)open(a[(f->i + 1)], O_RDWR | O_CREAT, 00777);
}

void						invalid_option(t_flags *f, char **a)
{
	f += 0;
	a += 0;
	ft_printf("Invalid Option Flag\n");
}
