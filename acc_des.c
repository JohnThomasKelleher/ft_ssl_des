
#include "hache.h"

void    initial_perm(t_flags *f)
{
  int a[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46,
    38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17,
    9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63,
    55, 47, 39, 31, 23, 15, 7
  };
  int i = 1; //is this right
  uint64_t x;
  uint64_t rev;
  
  f->ww = (uint64_t*)f->file;
  
  f->x = f->ww[0];
  while (i < 64)
    {
      x = f->x;
      x <<= a[i];
      x >>= 63;
      x <<= (64 - (i) - 1);//
      rev |= x;

      i++;
    }
  f->x = rev;
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

  
  rev = 0;
  while (i < 64)
    {
      x = f->x;
      x<<= a[i];
      x>>= 63;
      x<<= (64- (i) -1 );//
      rev |= x;

      i++;
    }
  f->x = rev;
}

/*void	parity_drop(t_flags *f)
{
  char *x;
  int i = 0;
  uint64_t new;

  new = 0;
  x = &f->in_key;
  while (i < 8)
    {
      x[i] >>= 1;
      i++;
    }
  i = 0;
  while (i < 8)
    {
      new <<= 6;
      new += x[i];
      i++;
    }
  f->in_key = new;
  
  }*/
uint32_t	lr_28(uint32_t x)
{
  
}

uint32_t	rr_28(uint32_t x)
{
  
}

void	parity_drop(t_flags *f)
{
  int a[56] = {
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 
    18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 
    44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 
    38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 
    28, 20, 12, 4
  };
  int i = 0;//is this right
  uint64_t x;
  uint64_t new;

  new = 0;
  while (i < 56)
    {
      x = f->in_key;
      x<<= a[i];
      hold &= 0x8000000000000000;//replace with macro
      x>>= 55;
      x<<= (56- (i) -1 );//
      new |= x;

      i++;
    }

  f->in_key = new;
}

uint64_t	comp_dbox(uint64_t b)
{
  int a[48] = {
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 
    10, 23, 19, 12, 4, 26, 8, 16, 7, 
    27, 20, 13, 2, 41, 52, 31, 37, 47, 
    55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 
    56, 34, 53, 46, 42, 50, 36, 29, 32
  };
  int i = 0;
  uint64_t hold;
  uint64_t new;

  while (i < 48)
    {
      hold = b;
      hold <<= a[i];
      hold &= 0x8000000000000000;//replace with macro
      hold >>= 47;
      hold <<= (48- (i) - 1);//
      new |= hold;

      i++;
    }
  return (new);
}


void	generate_keys_des(t_flags *f)
{
  uint32_t left;
  uint32_t right;
  int i = 0;
  uint64_t hold;
  
  left = ((f->key_in >> 36) << 36);
  right = ((f->key_in << 28) >> 28);
  
  while (i < 16)
    {
      left = lr_28(left);
      right = rr_28(right);
      if (i != 0 && i != 2 && i != 8 && i != 15)
	{
	  left = lr_28(left);
	  right = rr_28(right);
	}

      hold |= left;
      hold |= right;
      hold = comp_dbox(hold);
      f->keys[i] = hold;
     i++;
    }
  
}


uint8_t s1(uint8_t in)
{
  
}

uint8_t s2(uint8_t in)
{

}
uint8_t s3(uint8_t in)
{

}
uint8_t s4(uint8_t in)
{

}
uint8_t s5(uint8_t in)
{

}
uint8_t s6(uint8_t in)
{

}
uint8_t s7(uint8_t in)
{

}
uint8_t s8(uint8_t in)
{

}
