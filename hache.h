/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hache.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:00:15 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 16:59:08 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HACHE_H
# define HACHE_H
# define TWO_FIFTY(c) (c != 3 && c != 4)
# define OLD(f) (f->alg != base64)
# define HEX(f) ((f >= '0' and f <= '9') || (f >= 'A' && f <= 'Z') || (f >= 'a' && f <= 'z'))
# define NOT_DES(f) (f != ft_des && f != ft_des_ecb)
# define DES(a) (a[0] == 'd' && a[1] == 'e' && a[2] == 's')
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <iso646.h>

typedef struct s_ap				t_flags;
struct							s_ap
{
  int					dec_fd;
  uint8_t					decrypt;  
  uint8_t						first;
  uint64_t						salt;
  char							*password;
  uint64_t						orig_salt;
  uint8_t flush;
  uint8_t	a_op;
  int argc;
  uint8_t		invalid_key;
  	char						recent_letter;
  	uint8_t						decode;
  uint8_t				ecb;
  uint64_t				x_hold;
  uint64_t				x;
  uint32_t		l;
  uint32_t		f_hold;
uint32_t		ar;
  uint64_t	ex_r;
  uint64_t		*keys;
  uint64_t		in_key;
  void (**op) (t_flags *f, char **a);
	uint64_t					s0;
	uint64_t					s1;
	int							fd2;
	char						*name;
	void						(*alg) (t_flags *f);
	int							fd;
	uint32_t							ret;
	char						*file;
	char						*algy;
	int						hold;
	uint32_t					*kk;
	uint8_t						is_ne;
	uint8_t						never;
	uint8_t						p;
	uint8_t						q;
	uint8_t						r;
	uint8_t						st;
	uint8_t						det;
	uint32_t					*mm;
	uint32_t					*s;
	uint64_t					*k;
	uint64_t					orig_len;
	uint8_t						i;
	uint32_t					a_fin;
	uint32_t					b_fin;
	uint32_t					c_fin;
	uint32_t					d_fin;
	uint32_t					e_fin;
	uint32_t					f_fin;
	uint32_t					g_fin;
	uint32_t					h_fin;
	uint32_t					a;
	uint32_t					b;
	uint32_t					c;
	uint32_t					d;
	uint32_t					e;
	uint32_t					f;
	uint32_t					g;
	uint32_t					h;
	uint64_t					*ww;
	uint64_t					h0;
	uint64_t					h1;
	uint64_t					h2;
	uint64_t					h3;
	uint64_t					h4;
	uint64_t					h5;
	uint64_t					h6;
	uint64_t					h7;
	uint64_t					one;
	uint64_t					two;
	uint64_t					three;
	uint64_t					four;
	uint64_t					five;
	uint64_t					six;
	uint64_t					seven;
	uint64_t					eight;
	uint64_t					cha;
	uint64_t					t1;
	uint64_t					t2;
	uint64_t					mj;
	uint32_t					ch;
	uint32_t					nine;
	uint32_t					temp1;
	uint32_t					maj;
	uint32_t					temp2;
	uint32_t					*w;
	uint32_t					b_ind;
  
};

void unpack_base64(t_flags *f);
void                    other_ass_op(t_flags *f);
void    handle_file(t_flags *f, char **a);
void HMAC_md5(char *c, t_flags *f);
void                            help_me2(t_flags *f);
void    handle_pass(t_flags *f, char **a);
int                             			optns(t_flags *f, char **argv);
void							ft_des_ecb(t_flags *f);
void    						flip_buf(char *buf);
void 							reverse_four_bytes(char *x);
void							putstr_nonline(char *hold);
char							*getchar_64(char *buf);
void							print_keys(t_flags *f);
void							ass_dig(int *dig);
void							handle_des(t_flags *f, char **a);
void							initial_perm(t_flags *f);
void							final_perm(t_flags *f);
void							ft_des(t_flags *f);
uint8_t							s1(uint8_t in);
uint8_t							s2(uint8_t in);
uint8_t							s3(uint8_t in);
uint8_t							s4(uint8_t in);
uint8_t							s5(uint8_t in);
uint8_t							s6(uint8_t in);
uint8_t							s7(uint8_t in);
uint8_t							s8(uint8_t in);
void							generate_keys_des(t_flags *f);
void							base64(t_flags *f);
uint32_t						left_rotate(uint32_t n, uint32_t d);
void							ass_op(t_flags *f);
void							parse(t_flags *f, char **argv);
void							ft_md5(t_flags *f);
char							*append(t_flags *f);
uint32_t						*ft_make_s(void);
uint32_t						*ft_make_k(void);
uint64_t						*sha_make_k(uint64_t *k, t_flags *f);
void							initi(t_flags *f);
void							ft_strin(t_flags *f, char **argv);
void							ft_writer(t_flags *f, char **argv);
void							ft_flags(t_flags *f, char **argv);
void							ft_stdin(t_flags *f, char **argv);
void							ft_quiet(t_flags *f, char **argv);
void							ft_err(t_flags *f);
int								smthing_thr(t_flags *f);
uint64_t						rr_64(uint64_t w, uint64_t r);
void							ft_64pad(char *buf, t_flags *f);
void							sha_512(t_flags *f);
int								sha_init_abc(t_flags *f);
int								sub_hash(t_flags *f);
uint32_t						rr(uint32_t w, uint32_t r);
uint32_t						*z_ero(uint32_t *w, t_flags *f);
uint64_t						*sha_make_k(uint64_t *k, t_flags *f);
void							accumulate(t_flags *f);
int								sha_initi(t_flags *f);
void							md5_hash(t_flags *f);
void							ft_putmd5(char *catch, t_flags *f);
void							ft_pad(char *buf, t_flags *f);
void							sha_256(t_flags *f);
void							sha_copy(char *w, char *buf, t_flags *f);
char							*sha_append(t_flags *f);
void							print256(char *p, t_flags *f);
#endif
