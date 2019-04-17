
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
      r_hold = f->r;
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
  f->r = 0;

  while (i > -1)
    {
      in = (f->ex_r % 64);
      f->ex_r /= 64;
      in = boxes[i](in);
      f->r <<= 4;
      f->r += in;
      
      i--;
    }
  
}

void str8_d_box(t_flags *f)
{
  
}

void	16_rounds(t_flags *f)
{
  int i = 0;
  while(i < 16)
    {
      expansion_des(t_flags *f); //does expansion from f->r to f->ex_r
      f->ex_r ^= f->keys[i];
      s_boxes(t_flags *f); //does sboxes to go from f->ex_r to f->r
      str8_d_box(t_flags *f); //does straight dboxing yo

      i++;
    }
}

void	print_cipher(t_flags *f)
{
  
}

void	des(t_flags *f)
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
