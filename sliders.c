
#include "hache.h"

void    expansion_des(t_flags *f)
{
  int a[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
  };
  int i = 0; //is this right
  uint64_t x;
  uint64_t res = 0;
  uint32_t r_hold;

  f->ex_r = 0;
  while (i < 48)
    {
      r_hold = f->ar;
      r_hold <<= (a[i] - 1);
      r_hold >>= 31;
      x = r_hold;
      x <<= (47 - (i));//
      res |= x;

      i++;
    }
  f->ex_r = res;
}

void    initial_perm(t_flags *f)
{
  int a[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46,
    38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17,
    9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63,
    55, 47, 39, 31, 23, 15, 7
  };
  int i = 0; //is this right
  uint64_t x;
  uint64_t rev = 0;
  uint64_t hold = 0;
  f->ww = (uint64_t*)f->file;

  f->x = f->ww[0];
  //printf("\ni: %d, before data: %llx\n", i, f->x);
  //printf("before ip: %llu, ", f->x);
  while (i < 64)
    {
      x = f->x;
      x <<= (a[i] - 1);
      x >>= 63;
      x <<= (63 - (i));//
      rev |= x;

      i++;
    }
  f->x = rev;
  //printf("after ip: %llu\n", f->x);
  f->ar = ((f->x << 32) >> 32);
  hold = ((f->x >> 32) << 32);
  f->l = (hold >>32);
  //printf("left: %u, right: %u\n", f->l, f->ar);
}

void final_perm(t_flags *f)
{
  int a[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46,
    14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20,
    60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33,
    1, 41, 9, 49, 17, 57, 25
  };
  int i = 0; //is this right
  uint64_t x;
  uint64_t rev;
  uint64_t left = 0;

  rev = 0;
  f->x = 0;
  f->x |= f->ar;
  left = f->l;
  left <<= 32;
  f->x |= (left);
  while (i < 64)
    {
      x = f->x;
      x<<= (a[i] - 1);
      x>>= 63;
      x<<= (64- (i) -1 );//
      rev |= x;

      i++;
    }
  f->x = rev;
  //printf("f->x %llx\n", f->x);
}

void    parity_drop(t_flags *f)
{
  int a[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
  };
  int i = 0;//is this right
  uint64_t x;
  uint64_t new;

  new = 0;
  while (i < 56)
    {
      x = f->in_key;
      x <<= (a[i] - 1);
      x >>= 63;
      x <<= (55- (i));//
      new |= x;

      i++;
    }

  f->in_key = new;
}

uint64_t        comp_dbox(uint64_t b)
{
  int a[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
  };
  int i = 0;
  uint64_t hold;
  uint64_t new = 0;

  while (i < 48)
    {
      hold = b;
      //hold &= 0x8000000000000000;//replace with macro
      hold >>= (56 - a[i]);
      hold &= 1;
      hold <<= (47 - (i));//
      new |= hold;

      i++;
    }
  return (new);
}
