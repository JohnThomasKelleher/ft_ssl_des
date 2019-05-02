
#include "hache.h"

void pkcs7_pad(t_flags *f)
{
  uint8_t num = (8 - f->ret);
  int i = f->ret;

  while (i < 8)
    {
      f->file[i] = num;
      i++;
    }
}
