
#include "hache.h"

void	expansion_des(t_flags *f)
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
  //printf("before exp: %u, ", f->ar);
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
  //printf("after exp: %llu\n", f->ex_r);
}

void	reverse_half_bytes(t_flags *f)
{
  int i  = 0;
  uint32_t hold = 0;
  uint32_t other_hold = 0;

  while (i < 8)
    {
      other_hold = (f->f_hold & 0xF);
      f->f_hold >>= 4;
      hold <<= 4;
      hold += other_hold;
      i++;
    }
  f->f_hold = hold;
}

void	s_boxes(t_flags *f)
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

void str8_d_box(t_flags *f)
{
  int a[32] = {
    15, 6, 19, 20, 28, 11, 27, 16, 0, 14, 22, 25, 4, 17, 30, 9, 1, 7, 23, 13, 31, 26, 2, 8, 18 , 12, 29, 5, 21, 10, 3, 24
  };
  int i = 0; //is this right
  uint32_t x;
  uint32_t rev;

  rev = 0;
  while (i < 32)
    {
      x = f->f_hold;
      x <<= a[i];
      x >>= 31;
      x <<= (32 - (i) - 1);//
      rev |= x;

      i++;
    }
  f->f_hold= rev;
}

void swap_lr(t_flags *f)
{
  uint32_t hold;
  hold = f->l;
  f->l = f->ar;
  f->ar = hold;
}

void	print_keys(t_flags *f)
{
  int i = 0;
  while (i < 16)
    {
      printf("i: %d, key: %llx\n", i, f->keys[i]);
      i++;
    }
}

void	ft_16_rounds(t_flags *f)
{
  int i = 0;
  while(i < 16)
    {
    
      expansion_des(f); //does expansion from f->r to f->ex_r
      //f->ar = 0;
      f->ex_r ^= f->keys[i];
      //printf("i: %d, before sbox: %llx, ", i, f->ex_r);
      s_boxes(f); //does sboxes to go from f->ex_r to f->f_hold
      //printf("after sbox: %x\n", f->f_hold);
      str8_d_box(f); //does straight dboxing on f_hold
      f->l ^= f->f_hold;
      if (i != 15)
	swap_lr(f); //swap left and right
      i++;
    }
}

int	print_cipher(t_flags *f)
{
  //printf("f->ar: %x\n", f->ar);
  //printf("f->x: %llx\n", f->x);
  int i = 0;
  char *x;
  x = (char*) &f->x;
  flip_buf(x);
  while (i < 8)
    {
      write(1, &x[i], 1);
      write(1, " ", 1);//delete
      //printf("%02hhx", x[i]); 
      i++;
    }
  if (f->flush)
    write(1, "\n", 1);
  return (0);
}

void pkcs7_pad(t_flags *f)
{
  uint8_t num = (8 - f->ret);
  
  while (f->ret < 8)
    {
      f->file[f->ret] = num;
      f->ret++;
    }
} 
 
void	handle_des(t_flags *f, char **a)
{
  f->i++;
  if (!(f->fd = open(a[f->i], O_RDONLY)))
    {
      printf("sorry, no file there\n");
      return ;
    }
  //f->op['p'] = pbkdf;
  while (a[f->i])
    {
      if (a[f->i][0] == '-')
	f->op[(int)(a[f->i][1])](f, a);
      optns(f, a);
      f->i++;
    }
  f->alg(f);
}

void	flip_buf(char *buf)
{
  char hold;
  hold = buf[0];
  buf[0] = buf[7];
  buf[7] = hold;
  hold = buf[1];
  buf[1] = buf[6];
  buf[6] = hold;
  hold = buf[2];
  buf[2] = buf[5];
  buf[5] = hold;
  hold = buf[3];
  buf[3] = buf[4];
  buf[4] = hold;
}

void   handle_shit(char *buf, t_flags *f)
{
  uint64_t *hold;
  
  hold = (uint64_t*) buf;
  flip_buf(buf);
  //printf("before, data: %llu, as string: %s, after:", hold[0], buf);
  hold[0] ^= (f->ecb) ? (0) : (f->x);
  //printf("data: %llu, iv: %llu\n", hold[0], f->x);
}

void	putnstr(char *a, int len)
{
  int i = 0;

  while (i < len)
  {
    write(1, &a[i], 1);
    i++;
  }
}

void	base64_out(char *b, t_flags *f)
{
  uint32_t *c;
  uint32_t hold;
  char out;
  int i = 0;
  char s[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  
  //printf("c[0]: %x\n", c[0]);
  reverse_four_bytes(b);
  c = (uint32_t*)b;
  hold = (c[0]);
  //printf("c[0] %x\n", c[0]);
  while (i <= 3)
    {
      out = ((c[0] >> (26 - 6 * i)) & 0x3f);

      //printf("hold: %x\n", hold);
      //hold <<= 6;
      //printf(":::%u:::", f->ret);
      if (f->orig_len == 64)
	write(1, "\n", 1);
      if (hold)
	f->orig_len += write(1, &s[(int)out], 1);
      else
	write(1, "=", 1);
      hold <<= 6;
      i++;
    }
}

void	print_cipherB64(t_flags *f)
{
  static char b[4];
  int place_in_x = 0;
  static int place_in_b;
  uint32_t *x; 
  x = (uint32_t*)b;
//if 0, then two loops, 2 stored
  //if 1, then three loops, 0 stored
  //if 2, then three loops, 1 stored
  while (place_in_x <= 7)
    {
      b[place_in_b] = (f->x >> (56 - 8 * place_in_x)) & 0xff;
      place_in_x++;
      place_in_b++;
      if (place_in_b == 3)
	{
	  place_in_b = 0;
	  b[3] = '\0';
	  //printf("bvar: %x\n", x[0]);
	  base64_out(b, f);
	}
    }
  if (f->flush && place_in_b)
    {
      while (place_in_b <= 3)
	b[place_in_b++] = 0;
      //printf("bvar: %x\n", x[0]);
      base64_out(b, f);
    }
  if (f->flush)
    write(1, "\n", 1);
}

void	ft_des_ecb(t_flags *f)
{
  f->ecb = 1;
  ft_des(f);
}

void	ft_des(t_flags *f)
{
  //printf("entering des, fd = %d\n", f->fd);
  char buf[9];
  int i = 0;

  f->keys = (uint64_t*)malloc(sizeof(int) * 17);
  generate_keys_des(f);
  while (8 == (f->ret = read(f->fd, buf, 8)))
    {
      //printf("i: %d", i);
      handle_shit(buf, f);
      buf[f->ret] = '\0';
      f->file = buf;
  initial_perm(f);
  ft_16_rounds(f);
  final_perm(f);
  //(f->ecb) ? (print_cipher(f)) : (0);
  //printf("i: %d, after data: %llx\n", i, f->x);
  //printf("a_op: %hhu\n", f->a_op);
  (f->a_op) ? (print_cipherB64(f)) : (print_cipher(f));
  i++;
    }
  f->file = buf;
  pkcs7_pad(f);
  //printf("i: %d, ", i);
  
  handle_shit(buf, f);
  
initial_perm(f);
  ft_16_rounds(f);
  final_perm(f);
  
  //printf("i: %d, after data: %llx\n", i, f->x);
  f->flush = 1;
  (f->a_op) ? (print_cipherB64(f)) : (print_cipher(f));
  //printf("f->x: %llx\n", f->x);
  //print_cipher(f);
}
