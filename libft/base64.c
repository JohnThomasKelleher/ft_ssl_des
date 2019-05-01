/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hache.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:00:15 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 16:59:08 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.c"

char *getchar_64(char *buf)
{
  char x[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  
  int i = 0;
  int *a;
  char *ret;
  int temp = 0;
  
  ret = (char*)malloc(sizeof(char) * 4);
  a = (int *)buf;
  while (a[0])
    {
      temp = a[0] % 64;
      ret[i++] = x[temp];
      a[0] /= 64;
    }
  while (i < 4)
      ret[i++] = '=';
  ret[i] = '\0';
  return (ret);
}

void	base64(t_flags *f)
{
  char buf[4];
  char *hold;

  //f = (char*) malloc(sizeof(char) * 5);
  f->fd = (f->st) ? (uint32_t)open("./del", O_RDONLY) : (f->fd);
  while ((f->ret = read(f->fd, buf, 3)))
    {
      buf[f->ret] = '\0';
      hold = getchar_64(buf);
      ft_strjoin(f->file, hold);
    }
}
