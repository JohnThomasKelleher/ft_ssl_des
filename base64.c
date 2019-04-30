/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:00:15 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 16:59:08 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

unsigned int reverse_bits(unsigned int x)
{
  int i = 0;
  unsigned int a;
  unsigned int rev = 0;
  a = x;
  unsigned int hold;
  //printf("%u\n", a[0]);
  while (i < 32)
    {
      hold = a;
      hold <<= i;
      hold >>= (31);
      hold <<= i;
      rev |= hold;
      i++;
    }
  //printf("%u\n", rev);
  return (rev);
}

unsigned char	reverse_bits_char(unsigned char x)
{
  int i = 0;
  unsigned char a;
  unsigned char rev = 0;
  a = x;
  unsigned char hold;
  //printf("%u\n", a[0]);
  while (i < 8)
    {
      hold = a;
      hold <<= i;
      hold >>= 7;
      hold <<= i;
      rev |= hold;
      i++;
    }
  //printf("%u\n", rev);
  rev >>= 2;
  
  return (rev);
}

void reverse_four_bytes(char *x)
{
  unsigned int h[4];

  h[0] = x[0];
  h[1] = x[1];
  h[2] = x[2];
  
  x[0] = x[3];
  x[1] = h[2];
  x[2] = h[1];
  x[3] = h[0];
 
  
}

char *getchar_64(char *buf)
{
  char x[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  
  int i = 0;
  unsigned int *a;
  char *ret;
  unsigned int temp = 0;
  
  ret = (char*)malloc(sizeof(char) * 4);
  a = (unsigned int*)buf;
  a[0] = reverse_bits(a[0]);
  reverse_four_bytes((char*)a);
  while (a[0])
    {
      temp = a[0] % 64;
      temp = reverse_bits(temp); //this must be broken
      temp >>= 26;
      //printf("\ni: %d temp: %u a[0]: %u", i, temp, a[0]);
      ret[i++] = x[temp];
      //a[0] >>= 6;
      a[0] /= 64;
    }
  while (i < 4)
      ret[i++] = '=';
  ret[4] = '\0';
  return (ret);
}

void	putstr_nonline(char *hold)
{
  int i = 0;
  
  while (hold[i] != '\0')
    {
      write(1, &hold[i], 1);
      i++;
    }
}

//char	decode_char64(unsigned int)

void	print_decode64(unsigned int x, int old_i, t_flags *f)
{
  char *y;
  x >>= 8;
  y = (char*)&x;
  
  //printf("hold: %u old_i: %d\n", x, old_i);

  int i = old_i -2;
  //(f->decrypt) ? (
  //int stop = old_i - 1;
  f->dec_fd = (f->dec_fd == 0) ? (1) : (f->dec_fd);
  while (i >= 0)
    {
      //printf("val: %hhu i: %d\n", y[i], i);
      //write(1, &y[i], 1);
      //printf("i: %d\n", i);
      write(f->dec_fd, &y[i], 1);
      //printf("i: %d", i);
      i--;
    }
}

unsigned char	find_index(char buf)
{
  char s[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  unsigned char i = 0;
  
  while (i < 64)
    {
      if (s[i] == buf)
	return (i);
      i++;
    }
  return (0);
}

void unpack_base64(t_flags *f)
{
  remove("./del2");
  f->dec_fd = (uint32_t)open("./del2", O_RDWR | O_CREAT, 00777);
  f->decode = 1;
  decode_base64(f);
  f->fd = f->dec_fd;
  close(f->fd);
  f->fd = open("./del2", O_RDWR);
}

void	handle_B64(t_flags *f, char **a)
{
  while (a[f->i] != '\0')
    {
      if (a[f->i][0] == '-')
	f->op[(int)a[f->i][1]](f, a);
      f->i++;
    }
  if (f->fd <= 0)
    f->fd = 0;
  if (f->decrypt)
    decode_base64(f);
  else
    base64(f);
}

void rem_whitespace(t_flags *f)
{
  char buf[1];
  int fd_hold = 0;
  
  remove("./del3");
  fd_hold = open("./del3", O_RDWR | O_CREAT, 00777);
  while(0 < read(f->fd, buf, 1))
    {
      if (buf[0] != ' ' && buf[0] != 9 && buf[0] != '\n')
	write(fd_hold, &buf[0], 1);
    }
  if (f->fd != 0)
    close(f->fd);
  f->fd = fd_hold;
  close(f->fd);
}

void decode_base64(t_flags *f)
{
  //printf("fd: %d\n", f->fd);
  unsigned int hold;
  char buf[5];
  uint8_t x;
  int i = 0;

  rem_whitespace(f);
  f->fd = open("./del3", O_RDWR);
  while (1 < (f->ret = read(f->fd, buf, 4)))
    {
      //printf("buf: %s, ", buf);
      buf[f->ret] = '\0';
      //printf("f->ret: %d\n", f->ret);
      hold = 0;
      i = f->ret - 1;
      while (i >= 0)
	{
	  //printf("%d buf[i] = %c\n", i, buf[i]);
	  x = find_index(buf[i]);
	  //printf("x: %hhu\n", x);
	  //printf("%d x = %hhu\n", i, x);
	  
	  x = reverse_bits_char(x);
	  //printf("%d reversed x = %hhu\n", i, x);
	  hold <<= 6;
	  hold |= x;

	  //printf("%d hold: %u\n", i, hold);
	  //printf("\n");
	  i--;
	}
 
      //printf("BEFORE buf[0]: %hhu hold: %u ret: %d \n",buf[0],  hold, f->ret);
      hold = reverse_bits(hold);
      //printf("hold: %x\n", hold);
      //printf("AFTER buf[0]: %hhu hold: %u ret: %d \n",buf[0],  hold, f->ret);
      //printf("f->ret: %d\n", f->ret);
     print_decode64(hold, f->ret, f);
    }
}

void	base64(t_flags *f)
{
  char buf[4];
  char *hold;

  //f->fd = (f->st) ? (uint32_t)open("./del", O_RDONLY) : (f->fd);

  while ((f->ret = read(f->fd, buf, 3)))
    {
      buf[3] = 0;
      buf[2] = (f->ret == 2) ? (0) : (buf[2]);
      buf[1] = (f->ret == 1) ? (0) : (buf[1]);

      hold = getchar_64(buf);
      putstr_nonline(hold);
      //ft_strjoin(f->file, hold);
    }
  write(1, "\n", 1);
  
}
 

/*

steps for tomorrow:
-ignore spaces
-move to the next part

 */
