
#include "hache.h"

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
}

uint32_t	lr_28(uint32_t n, uint32_t d)
{

  uint32_t hold;
  uint32_t res = 0;
  hold = n;
  
  
  res = ((n << d));
  res &= 0xFFFFFFF;
  res |= (n >> (28 - d));
  return (res);
  

}

uint32_t	rr_28(uint32_t n, uint32_t d)
{
  d = ((n >> d) | (n <<(28 - d)));
  d &= 0xFFFFFFF;
  return (d);
}

void	parity_drop(t_flags *f)
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

uint64_t	comp_dbox(uint64_t b)
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

void ass_dig(int *dig)
{
  dig['0'] = 0;
  dig['1'] = 1;
  dig['2'] = 2;
  dig['3'] = 3;
  dig['4'] = 4;
  dig['5'] = 5;
  dig['6'] = 6;
  dig['7'] = 7;
  dig['8'] = 8;
  dig['9'] = 9;
  dig['a'] = 10;
  dig['A'] = 10;
  dig['b'] = 11;
  dig['B'] = 11;
  dig['c'] = 12;
  dig['C'] = 12;
  dig['d'] = 13;
  dig['D'] = 13;
  dig['e'] = 14;
  dig['E'] = 14;
  dig['f'] = 15;
  dig['F'] = 15;
}


void read_key(t_flags *f, char **a)
{
  char buf[1];
  int dig[123];
  uint64_t ret = 0;

  a += 0;
  ass_dig(dig);
  write(1, "Enter Key in Hex: \n", 19);
  while (read(0, buf, 1))
    {
      ret *= 16;
      if (!HEX(buf[0]))
	{
	  f->invalid_key = 1;
	  return ;
	}
      ret += dig[(int)buf[0]];
    }
  f->in_key = ret;
}

void	generate_keys_des(t_flags *f)
{
  uint32_t left;
  uint32_t right;
  int i = 0;
  uint64_t hold;
  uint8_t shift;

  //f->in_key = 0x4080808080808080;
  //read_key(f);
  //printf("before parity: %llx\n", f->in_key);
  parity_drop(f);
  //printf("after parity: %llx\n", f->in_key);
  left = (f->in_key >> 28);// << 36);
  right = (f->in_key & 0xfffffff);
  //printf("left: %x, right %x\n", left, right);
  
  while (i < 16)
    {
      shift = (i == 0 || i == 1 || i == 8 || i == 15) ? (1) : (2);
     
      //printf("before: left: %x, right %x\n", left, right);
      left = lr_28(left, shift);
      right = lr_28(right, shift);
      //printf("shifted: %d, left: %x, right %x\n\n",shift,  left, right);
      hold = 0;
      hold |= (left);
      hold <<= 28;
      hold |= right;
      //printf("before box: %llx, ", hold);

      hold = comp_dbox(hold);
      //printf("after box: %llx\n", hold);
      f->keys[i] = hold;
     i++;
    }
  //print_keys(f);
}


uint8_t s1(uint8_t in)
{  
  uint8_t box[64] = {0, 14, 15, 4, 7, 13, 4, 1, 14, 2, 2, 15, 13, 11, 1, 8, 10, 3, 6, 10, 12, 6, 11, 12, 9, 5, 5, 
9, 3, 0, 8, 7, 15, 4, 12, 1, 8, 14, 2, 8, 4, 13, 9, 6, 1, 2, 7, 11, 5, 15, 11, 12, 3, 9, 14, 7, 10, 3, 0, 10, 6, 5, 13, 0 };
  
  return (box[in]);
}

uint8_t s2(uint8_t in)
{
  uint8_t box[64] = { 3, 15, 13, 1, 4, 8, 7, 14, 15, 6, 2, 11, 8, 3 ,14, 4, 12, 9, 0, 7, 1, 2, 10, 13, 6, 12, 9, 0, 11, 5, 
		      5, 10, 13, 0, 8, 14, 10, 7, 1, 11, 3, 10, 15, 4, 4, 13, 2, 1, 11, 5, 6, 8, 7, 12, 12, 6, 0, 9, 5, 3, 14, 2, 9, 15
};

  return (box[in]);
}
uint8_t s3(uint8_t in)
{
  uint8_t box[64] = { 13, 10, 7, 0, 0, 9, 9, 14, 3, 6, 4, 3, 6, 15, 10, 5, 2, 1, 8, 13, 5, 12, 14, 7, 12, 11, 11, 4, 
		      15, 2, 1, 8, 1, 13, 10, 6, 13, 4, 0, 9, 6, 8, 9, 15, 8, 3, 7, 0, 4, 11, 15, 1, 14, 2, 3, 12, 11, 5, 5, 10, 2, 14, 12, 7
  };
  return (box[in]);
}
uint8_t s4(uint8_t in)
{
  uint8_t box[64] = {
    13, 7, 8, 13, 11, 14, 5, 3, 6, 0, 15, 6, 0, 9, 3, 10, 4, 1, 7, 2, 2, 8, 12, 5, 1, 11, 10, 12, 14, 4, 9, 15, 3, 
    10, 15, 6, 0, 9, 6, 0, 10, 12, 1, 11, 13, 7, 8, 13, 9, 15, 4, 1, 5, 3, 11, 14, 12, 5, 7, 2, 2, 8, 14, 4
  };
  return (box[in]);
}
uint8_t s5(uint8_t in)
{
  uint8_t box[64] = {
    14, 2, 11, 12, 2, 4, 12, 1, 4, 7, 7,10, 13, 11, 1, 6, 5, 8, 0, 5, 15, 3, 10 ,15, 3, 13, 9, 0, 8, 14, 6, 9, 11, 
    4, 8, 2, 12, 1, 7, 11, 1, 10, 14, 13, 2, 7, 13, 8, 6, 15, 15, 9, 0, 12, 9, 5, 10, 6, 4, 3, 5, 0, 3, 14
  };
  return (box[in]);
}
uint8_t s6(uint8_t in)
{
  uint8_t box[64] = {
    10, 12, 15, 1, 4, 10, 2, 15, 7, 9,12, 2, 9, 6, 5, 8, 6, 0, 1, 13, 13, 3, 14, 4, 0, 14, 11, 7, 3, 5, 8, 11, 4, 
    9, 3, 14, 2, 15, 12, 5, 9, 2, 5, 8, 15, 12, 10, 3, 11, 7, 14, 0, 1, 4, 7, 10, 6, 1, 0, 13, 8, 11, 13, 6 
  };
  return (box[in]);
}
uint8_t s7(uint8_t in)
{
  uint8_t box[64] = {
    13, 4, 0, 11, 11, 2, 7, 14, 4, 15, 9, 0, 1, 8, 10 ,13, 14, 3, 3, 12, 5, 9, 12, 7, 2, 5, 15, 10, 8, 6, 6, 
    1, 6, 1, 11, 4, 13, 11, 8, 13, 1, 12, 4, 3, 10, 7, 7, 14, 9, 10, 5, 15, 0, 6, 15, 8, 14, 0, 2, 5, 3, 9, 12, 2
  };
  return (box[in]);
}
uint8_t s8(uint8_t in)
{
  uint8_t box[64] = {
    1, 13, 15, 2, 13, 8, 8, 4, 10, 6, 3, 15, 7, 11, 4, 1, 12, 10, 5, 9, 6, 3, 11, 14, 0, 5, 14, 0, 9, 12, 2 ,7, 2, 7,
    1, 11, 14, 4, 7, 1, 4, 9, 10, 12, 8, 14, 13, 2, 15, 0, 12, 6, 9, 10, 0, 13,3,  15, 5, 3, 6, 5, 11, 8
  };
  return (box[in]);
}

