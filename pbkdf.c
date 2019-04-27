


#include "hache.h"

uint64_t	get_salt(void)
{
  uint64_t *ret;
  int fd = 0;
  char buf[8];
  ret = (uint64_t*)buf;

  fd = open("/dev/random", O_RDONLY);
  read(fd, buf, 8);
  return (ret[0]);
}

/*
only store the front (A || B) 64 bits of the output, this is the key.  to concat S with i by 64bit array, the taking more significant half of second item in array. 
 */

void pad_HMAC(t_flags *f)
{
  int i = 0;

  while (f->password[i] != '\0')
      i++;
  while (i < 64)
    {
      f->password[i] = 0;
      i++;
    }
}

void conc(char *concat, uint64_t a, uint64_t b)
{
  char *x;
  char *y;
  
  x = (char*)&a;
  y = (char*)&b;
  int i = 0;
  while (i < 8)
    {
      concat[i] = (i < 4) ? (x[i]) : (y[(i - 4)]);
      i++;
    }
}

void HMAC_md5_pad(char *c, int len)
{
  int len_in_bits = (len * 8);
  char *hold;
  int i = 0;

  hold = (char*)&len_in_bits;
  c[len] = -128;
  while (len <= 56)
    {
      c[len] = 0;
      len++;
    }
  
  while (len <= 64)
    {
      c[len] = hold[i];
      i++;
      len++;
    }
}

void HMAC_md5(char *c, t_flags *f)
{
  f->mm = (uint32_t*)c;
  
  md5_hash(f);
  help_me2(f);
}

void	HMAC(t_flags *f)
{
  int blockSize = 64;
  //message is f->salt
  //key is f->password
  uint64_t o_key = 0;
  uint64_t i_key = 0;
  int len = ft_strlen(f->password);
  uint64_t *key;
  char concat[65];
  uint64_t AB = 0;
  
  key = (uint64_t*)f->password;
  if (len > 64)
    {
      f->password = handle_big_HMAC(f);
    }
  else if (len < 64)
    pad_HMAC(f);//pad with 0s till 64 bytes

  o_key = key[0] ^ (0x5c * blockSize);//key might need to be flipped before these;
  i_key = key[0] ^ (0x36 * blockSize);
  
  //return (ft_md5(o_key concat ft_md5(i_Key concat f->salt));
  conc(concat, i_key, f->salt);//16 bytes
  concat[16] = (1) ;
  int mssg_len = (f->first) ? (17) : (16);
  HMAC_md5_pad(concat, mssg_len);
  HMAC_md5(concat, f);
  AB += f->a_fin;
  AB <<= 32;
  AB += f->b_fin;
  conc(concat, o_key, AB);// 16 bytes
  HMAC_md5_pad(concat, 16);
  HMAC_md5(concat, f);
  AB +=f->a_fin;
  AB <<= 32;
  AB +=f->b_fin;
  return (AB);
}

void	handle_pass(t_flags *f, char **a)//make salt, and key(and pass?) and print if option on
{
  int c = 0;
  int iterations = 2048;
  uint64_t out = 0;
  uint64_t running = 0;

  f->password = a[(f->i+1)];
  f->orig_salt = get_salt();
  f->salt = f->orig_salt;
  f->first = 1;
  while (c < iterations)
    {
      out = HMAC(f);//
      f->salt = out;
      running |= out;
      f->first = 0;
      c++;
    }
  f->in_key = running;
}
