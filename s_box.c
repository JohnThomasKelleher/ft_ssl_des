
#include "hache.h"

void    s_boxes(t_flags *f)
{
  uint8_t (*boxes[8]) (uint8_t) = { s1, s2, s3, s4, s5, s6, s7, s8 };
  int i = 7;
  uint8_t in = 0;
  //f->ar = 0;
  while (i > -1)
    {
      in = (f->ex_r % 64);
      f->ex_r /= 64;
      in = boxes[i](in);
      f->f_hold <<= 4;
      f->f_hold += in;

      i--;
    }
  //printf("before flipping half bytes: %x\n", f->f_hold);
  reverse_half_bytes(f);

}

