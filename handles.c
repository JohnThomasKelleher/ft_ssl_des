
#include "hache.h"

void    handle_flags(t_flags *f, char **a)
{
  if (a[f->i][1] == 'a')
    f->a_op = 1;
  if (a[f->i][1] == 'p')
    {
      f->p = 1;
      f->password = a[(f->i+1)];
    }
  if(a[f->i][1] == 'd')
    f->decrypt = 1;
}

void    handle_file(t_flags *f, char **a)
{
  if (0 > (f->fd = open(a[(f->i + 1)], O_RDONLY)))
    {
      ft_printf("sorry, no file there\n");
      return ;
    }
}

void	write_salt(t_flags *f)
{
  //acts on f->x, 8 bytes at a time
  char buf[9] = { 'S', 'a', 'l', 't', 'e', 'd', '_', '_' };
  uint64_t *b;
  uint64_t hold;
  
  f->orig_len_des = 0;
  f->flush = 0;
  hold = f->x;
  b = (uint64_t*)buf;
  flip_buf(buf);
  f->x = b[0];
  (f->a_op) ? (print_cipherB64(f)) : (print_cipher(f));
  //flip_buf((char*)&f->orig_salt);
  f->x = f->orig_salt;
  //flip_buf((char*)&f->orig_salt);
  (f->a_op) ? (print_cipherB64(f)) : (print_cipher(f));
  f->x = hold;
  f->orig_len_des = 20;
}

void other_set_hex(t_flags *f, char *a)
{
  uint64_t *ret;
 
  flip_buf(a);
  ret = (uint64_t*)a;
  f->orig_salt = ret[0];
  //printf("salt: %llx\n", ret[0]);
}

int cmp_salt(char *buf, char *salt)
{
  int i = 0;
  while (buf[i] != '\0' && salt[i] != '\0')
    {
      if (buf[i] != salt[i])
	return (1);
      i++;
    }
  if (buf[i] != salt[i])
    return (1);
  return (0);
}

void	read_salt(t_flags *f)
{
  char salt[9] = { 'S', 'a', 'l', 't', 'e', 'd', '_', '_' };
  char buf[9];

  (read(f->fd, buf, 8));
    //printf("you suck!\n");
     cmp_salt(buf, salt);
    //ft_printf("bad magic number\n");
     (read(f->fd, buf, 8));
    //printf("you suck!\n");
  other_set_hex(f, buf);
}

void    handle_des(t_flags *f, char **a)
{
  int hold_fd;

  f->is_iv = 0;
  f->fd_out = 1;
  f->a_op = 0;
  hold_fd = 0;
  optns(f, a);
  f->i++;
  while (a[f->i])
    {
      if (a[f->i][0] == '-')
        f->op[(int)(a[f->i][1])](f, a);
      optns(f, a);
      f->i++;
    }

  if (f->p && !f->decrypt) 
    write_salt(f);
  f->fd = (f->fd > 0) ? (f->fd) : (0);
  (f->decrypt && f->a_op) ? (unpack_base64(f)) : (0); //set f->dec_fd to a new file, puts decoded into f->fd
  if (f->p && f->decrypt)
    {
      //read off 16 bytes, confirm first 8 salted, parse next 8 for salt
      read_salt(f);
    }
  if (f->p)
    {
      hold_fd = f->fd;
      handle_pass(f, a);
      f->fd = hold_fd;
    }
  //printf("salt: %llx\n", f->orig_salt);
  //printf("key: %llX\n, iv: %llX\n", f->in_key, f->x);
  (f->alg) ?  (f->alg(f)) : (0);
}

void   handle_shit(char *buf, t_flags *f)
{
  uint64_t *hold;
  hold = (uint64_t*) buf;
  flip_buf(buf);
  f->pt_carry = (f->first) ? (f->x) : (f->prev);
  f->prev = hold[0];
  hold[0] ^= (f->ecb || f->decrypt) ? (0) : (f->x);
  f->first = 0;

}
