
#include "hache.h"

uint64_t        get_salt(void)
{
  uint64_t *ret;
  int fd = 0;
  char buf[8];
  ret = (uint64_t*)buf;

  fd = open("/dev/random", O_RDONLY);
  read(fd, buf, 8);
  return (ret[0]);
}

void  ft_the_writer(t_flags *f, char *x, int len)
{
  int i;

  i = 0;
  while (i < len)
    {
      //write(1, &x[i], 1);
      write(f->fd, &x[i], 1);
      i++;
    }
}

void  ft_pwdin(t_flags *f, char **x, int len)
{
  remove("./del");
  f->never = 0;
  f->st = 1;
  //f->i++;
  //f->name = argv[f->i];
  f->st = 1;
  f->fd = (uint32_t)open("./del", O_RDWR | O_CREAT, 00777);
  ft_the_writer(f, x[0], len);
  //f->i = 0;
  ft_md5(f);
  f->file = NULL;
  f->st = 0;
  //f->hold++;
  close(f->fd);
  remove("./del");
}

int concat(char **x, t_flags *f)
{
  char *hold;
  int len = ft_strlen(f->password);
  
  hold = (char*)&f->orig_salt;
  x[0] = (char*)malloc(sizeof(char) * (len + 9));
  int i = 0;
  while (f->password[i] != '\0')
    {
      x[0][i] = f->password[i];
      i++;
    }
  int j = 0;
  flip_buf(hold);
  while (j < 8)
    {
      x[0][i] = hold[j];
      j++;
      i++;
    }
  //x[0][i] = '\0';
  return (i);
}

void handle_pass(t_flags *f, char **a)
{
  char **x;
  int len;

  a+=0;
  x = (char **)malloc(sizeof(char*) *2);
  initi(f);
  f->s = ft_make_s();
  f->kk = ft_make_k();
  f->b_ind = 0;
  f->orig_salt = (f->orig_salt) ? (f->orig_salt) : (get_salt());
  f->salt = f->orig_salt;
  //printf("salt=%llX\n", f->salt);
  //concat password || salt. null term, dont need length. REWRITE TO USE LENGHT NOT NULL TERM
  len = concat(x, f);
  //printf("len: %d\n", len);
  //send to pwdin as x[0]
  f->orig_len = 0;//********************************************
  ft_pwdin(f, x, len);
  //f->a_fin conc with f->b_fin
  f->in_key = 0;
  f->in_key += f->b_fin;
  f->in_key <<= 32;
  f->in_key += f->a_fin;
  f->x += f->d_fin;
  f->x <<= 32;
  f->x += f->c_fin;
  flip_buf((char*)&f->x);
  flip_buf((char*)&f->in_key);
  //printf("key=%llX\n", f->in_key);
	 free(x[0]);
	 free(x);
}
    
