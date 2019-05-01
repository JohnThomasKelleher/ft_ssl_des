


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
  while (i < 16)
    {
      concat[i] = (i < 8) ? (x[i]) : (y[(i - 8)]);
      i++;
    }
}

void HMAC_md5_pad(char *c, int len, t_flags *f)
{
  uint64_t len_in_bits = (len * 8);
  char *hold;
  int i = 0;

  //f->first && printf("len: %d\n", len);
  hold = (char*)&len_in_bits;
  c[len++] = -128;
  while (len != 56 && len != 120)
    {
      c[len] = 0;
      len++;
    }
  while (len != 64 && len != 128)
    {
      c[len] = hold[i];
      i++;
      len++;
    }
  HMAC_md5(c, f);
  //(f->first) ? (printf("a, ", len)) : (0);
  if (len == 128)
    HMAC_md5((c + 64), f);
}

int	print_block(char *c)
{
  int i = 0;

  printf("block: ");
  while (i < 64)
    {
      printf("%hhx ", c[i]);
      i++;
    }
  printf("\n");
  return (1);
}

void	print_out(char *c)
{
  int i = 0;

  while (i< 16)
    {
      printf("%hhx", c[i]);
      i++;
    }
}

void HMAC_md5(char *c, t_flags *f)
{
  f->mm = (uint32_t*)c;
  //f->first && printf("c[19]%hhx\n", c[19]);
  f->first && print_block(c);
  md5_hash(f);
  help_me2(f);
}

void	handle_big_HMAC(t_flags *f, uint64_t *AB)
{
  int i = 0;

  initi(f);
  f->mm = (uint32_t*) (f->password);
  md5_hash(f);
  help_me2(f);
  while (f->password[i] != '\0')
    {
      i++;
      if (i % 64 == 0)
	{
	  //initi(f);
	  f->mm = (uint32_t*) (f->password + i);
	  md5_hash(f);
	  help_me2(f);
	}
    }
  if (i % 64 > 55)
    {
      while (i != 120)
	f->password[i++] = 0;

      HMAC_md5_pad(f->password, i, f);
    }
  else
    HMAC_md5_pad(f->password, i, f);
  AB[0] += f->a_fin;
  AB[0] <<= 32;
  AB[0] += f->b_fin;
  f->password = (char*)AB;
}

void big_end_one(char *c)
{
  c[16] = 0;
  c[17] = 0;
  c[18] = 0;
  c[19] = 1;
  c[20] = '\0';
}

uint64_t	HMAC(t_flags *f)
{

  //message is f->salt
  //key is f->password
  uint64_t o_key = 0;
  uint64_t i_key = 0;
  int len = 0;//ft_strlen(f->password);DEBUG
  f->salt = 0;
  uint64_t *key;
  char concat[65];
  uint64_t AB = 0;
  char *catch;
  f->first && printf("\n\n\n");
  key = (uint64_t*)f->password;
  if (len > 64)
    {
      handle_big_HMAC(f, &AB);
    }
  else if (len < 64)
    pad_HMAC(f);//pad with 0s till 64 bytes

  key = (uint64_t*)f->password;
  uint32_t f_o = (0x5c * 64);
  uint32_t f_i = (0x36 * 64);
  //uint32_t f_o = 0xfo23 << 32;
  //uint32_t f_i = 0x1815 << 32;
  o_key = key[0] ^ (f_o);//key might need to be flipped before these;
  i_key = key[0] ^ (f_i);
  uint64_t *concatenated;
  concatenated = (uint64_t*)concat;
  //return (ft_md5(o_key concat ft_md5(i_Key concat f->salt));
  //(f->first) ? (printf("f->orig_salt: %llx\n", f->salt)) : (0);
  conc(concat, i_key, f->salt);//16 bytes
  //(f->first) ? (printf("i_key: %llx, i_key concat with f->salt: %llx\n", i_key, concatenated[0])) : (0);
  
  (f->first) ? (big_end_one(concat)) : (0);

  //f->first && printf("c[19]%hhx\n", concat[19]) && print_block(concat);
  //(f->first) ? (printf("i_key: %llx, i_key concat with f->salt: %llx\n", i_key, concatenated[0])) : (0);
  int mssg_len = (f->first) ? (20) : (16);
  initi(f);
  HMAC_md5_pad(concat, mssg_len, f);
  if (f->first)
    {
      printf("md5(i_key concat w/ salt), \n");
      
      catch = append(f);
      print_out(catch);
      //ft_putmd5(catch, f);
  printf("\n");
    }
  AB += f->a_fin;
  AB <<= 32;
  AB += f->b_fin;
  conc(concat, o_key, AB);// 16 bytes
  initi(f);
  HMAC_md5_pad(concat, 16, f);
  AB +=f->a_fin;
  AB <<= 32;
  AB +=f->b_fin;
  if (f->first)
    {
      printf("md5(o_Key concat w/ salt), \n");
      print_block((char*)&AB);
      printf("\n");
    }
  return (AB);
}

void	handle_pass(t_flags *f, char **a)//make salt, and key(and pass?) and print if option on
{
  int c = 0;
  int iterations = 2048;
  uint64_t out = 0;
  uint64_t running = 0;

  initi(f);
  f->s = ft_make_s();
  f->kk = ft_make_k();
  f->password = a[(f->i+1)];
  f->orig_salt = (f->orig_salt) ? (f->orig_salt) : (get_salt());
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
