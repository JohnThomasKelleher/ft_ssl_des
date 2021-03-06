/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/05/03 02:37:42 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void			fn(void (*fun[8]) (t_flags *f))
{
	fun[0] = ft_md5;
	fun[1] = sha_256;
	fun[2] = sha_256;
	fun[3] = sha_512;
	fun[4] = sha_512;
	fun[5] = base64;
	fun[6] = ft_des;
	fun[7] = ft_des;
	fun[8] = ft_des_ecb;
	fun[9] = NULL;
}

int				optns(t_flags *f, char **argv)
{
	const char	*op[] = {"md5", "sha256", "sha224",
	"sha512", "sha384", "base64", "des", "des-cbc", "des-ecb", NULL};
	void		(*fun[10]) (t_flags *f);
	int			j;

	fn(fun);
	j = 0;
	while (j <= 8)
	{
		if (ft_strcmp(op[j], argv[f->i]) == 0)
		{
			f->algy = (char*)op[j];
			f->det = j;
			f->alg = (void (*)(t_flags *))fun[j];
			return (1);
		}
		j++;
	}
	return (0);
}

void			parse2(t_flags *f, char **a)
{
	if (0 <= (f->fd = open(a[f->i], O_RDONLY)))
	{
		f->i = 0;
		f->name = a[f->hold];
		f->never = 0;
		f->alg(f);
	}
	else
		ft_printf("%s: No such file or directory\n", a[f->i]);
	f->i = f->hold;
	while (++f->i < f->argc)
		ft_printf("%s: No such file or directory\n", a[f->i]);
}

void			free_stuff(t_flags *f)
{
  if (!f->p)
    {
    free(f->kk);
    free(f->s);
    }
  free(f->op);
  free(f->keys);
  free(f);
}

void			parse(t_flags *f, char **a)
{
	if (DES(a[1]))
		return (handle_des(f, a));
	if (B64(a[1]))
		return (handle_b64(f, a));
	while (f->i < f->argc)
	{
		f->hold = f->i;
		if (a[f->i][0] == '-' && (f->recent_letter = a[f->i][1]))
			f->op[(int)(a[f->i][1])](f, a);
		else if (!optns(f, a))
		{
			parse2(f, a);
			return ;
		}
		f->i = (NOT_DES(f->alg)) ? (f->hold + 1) : (f->i + 1);
	}
	if (f->never && f->alg != ft_err && (f->is_ne = 1) && NOT_DES(f->alg))
		ft_stdin(f, a);
	free_stuff(f);
}
