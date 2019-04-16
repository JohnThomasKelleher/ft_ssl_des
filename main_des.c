
#include "hache.h"

void	16_rounds(t_flags *f)
{
  int i = 0;
  
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
