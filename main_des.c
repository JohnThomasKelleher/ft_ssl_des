
#include "hache.h"

void	expansion_des(t_flags *f)
{
  int a[64] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
  };
  int i = 1; //is this right
  uint64_t x;
  uint64_t res = 0;
  uint32_t r_hold;

  while (i < 64)
    {
      r_hold = f->ar;
      r_hold <<= a[i];
      r_hold >>= 31;
      x = r_hold;
      x <<= (48 - (i) - 1);//
      res |= x;

      i++;
    }
  f->ex_r = rev;
}

void	s_boxes(t_flags *f)
{
  uint8_t (boxes[8]) (uint8_t in) = { s1, s2, s3, s4, s5, s6, s7 };
  int i = 7;
  uint8_t in = 0;
  //f->ar = 0;

  while (i > -1)
    {
      in = (f->ex_r % 64);
      f->ex_r /= 64;
      in = boxes[i](in);
      f->ar <<= 4;
      f->ar += in;
      
      i--;
    }
  
}

void str8_d_box(t_flags *f)
{
  int a[32] = {
    15, 6, 19, 20, 28, 11, 27, 16, 0, 14, 22, 25, 4, 17, 30, 9, 1, 7, 23, 13, 31, 26, 2, 8, 18 , 12, 29, 5, 21, 10, 3, 24
  };
  int i = 0; //is this right
  uint32_t x;
  uint32_t rev;

  while (i < 32)
    {
      x = f->ar;
      x <<= a[i];
      x >>= 31;
      x <<= (32 - (i) - 1);//
      rev |= x;

      i++;
    }
  f->ar= rev;
}

void	16_rounds(t_flags *f)
{
  int i = 0;
  while(i < 16)
    {
      expansion_des(t_flags *f); //does expansion from f->r to f->ex_r
      f->ar = 0;
      f->ex_r ^= f->keys[i];
      s_boxes(t_flags *f); //does sboxes to go from f->ex_r to f->r
      str8_d_box(t_flags *f); //does straight dboxing yo

      i++;
    }
}

void	print_cipher(t_flags *f)
{
  printf("%u\n", f->ar);
  return ;
}

void	ft_des(t_flags *f)
{
  f->keys = (int*)malloc(sizeof(int) * 16);
  generate_keys_des(f);
  
  while (8 == (f->ret = read(f->fd, buf, 8)))
    {
      buf[f->ret] = '\0';
      f->file = buf;
  initial_perm(f);
  16_rounds(f);
  final_perm(f);
  print_cipher(f);
    }
}
