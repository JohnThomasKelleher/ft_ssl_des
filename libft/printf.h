/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:24:30 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/02 15:45:20 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include <locale.h>
# include <limits.h>

# define S(format) (ft_strchr("RpsSpdDioOuUxXcCbfFaA", format[-1]))
# define PREC2(format) (ft_strchr("hlL*.", format[-1]))
# define PREC1(format) (S(format) || PREC2(format))
# define U(format) (format[0] == 'U' || format[0] == 'D')
# define UDIGIT1(x) ((IS_UNSIGN(x) && x[-1] == 'l') || U(x))
# define PLUS(x) ((!O(x)) && (x->c[0] != 'u') && (!X(x)) && x->c[0] != 'p')
# define TH(x) (*x == 's' || *x == 'c')
# define THICC(x) (*x == 'S' || *x == 'C' || (x[-1] == 'l' && TH(x)))
# define BASETEN(x) (x == 'd' || x == 'D' || x == 'u' || x == 'U' || x == 'i')
# define INPUTS(x) (IS_TYPE(x) || isDIGIT(x) || isID(x) || isFLAG(x))
# define IS_UPPER(x) (x >= 'A' && x <= 'Z')
# define IS_LOW(x) (x >= 'a' && x <= 'z')
# define IS_TYPE(x) (ft_strchr("RpsSpdDioOuUxXcCbfFaA%", x) != NULL)
# define NUMBERS(x) (ft_strchr("dDxXboOuiU", *x))
# define FLOATS(x) (*x == 'f' || *x == 'F' || *x =='a' || *x == 'A')
# define ISDIGIT(x) (ft_strchr("0123456789", x))
# define HH(x) (x[-1] == 'h' && x[-2] == 'h')
# define LL(x) (x[-1] == 'l' && x[-2] == 'l')
# define IS_UNSIGN(x) (ft_strchr("xXoOu", *x))
# define P(x) (x->c[0] == 'p')
# define OX(x) (HASH(x) && (!x->zero || x->c[0] == 'p') && (X(x) || P(x)))
# define O(tree) (tree->c[0] == 'o' || tree->c[0] == 'O')
# define X(tree) (tree->c[0] == 'x' || tree->c[0] == 'X')
# define HASH(tree) (tree->hash && (!tree->zero || tree->c[0] == 'p'))
# define S3(x) (!x->l && !x->ll && !x->decimal && !x->hash && !x->plus)
# define S2(x) (x->space && !x->neg && !x->left && !x->percent && S3(x))
# define SINGLESPACE(x) ((ft_strchr("dif", x->c[0])) && S2(x))
# define P3(x) (x[i] != '\0' && x[(i - 1)] != '\0' && x[i] != 10)
# define P2(x) (x[i + 1] != '}' && x[(i + 1)] != '\0' && x[(i - 1)] != '\0')
# define P4(x) (P2(x) && P3(x))
# define PRINTF1(format) (!IS_TYPE(format[i]) && format[i] != '}' && P4(format))
# define PRINTF2(format) (format[i] == '\0' && format[(i -1)] == '%')
# define CONVZER(x) ((O(x) && !x->hash) || X(x) || ft_strchr("diup", x->c[0]))
# define F1(x) (x->dot && !x->z_pad)
# define FT_PAD1(x) ((x->zero && (CONVZER(x)) && (x->prec == 10000)) && F1(x))
# define FT_PAD2(x) (!(x->zero && x->dot && !x->z_pad) || FT_PAD1(x))
# define FLOOT(x) ((!x->prec || x->prec == 10000) && !x->dot)
# define FLO1(x) (x >= 0 && (((int)x % 10) != 2))
# define FLO2(x) (x < 0 && (((int)x % 10) != -2))

typedef struct s_ap				t_ap;

struct					s_ap
{
	int					len;
	int					prec;
	int					width;
	int					ret;
	uint8_t				preast;
	uint8_t				posast;
	uint8_t				left;
	uint8_t				percent;
	uint8_t				l;
	uint8_t				ll;
	uint8_t				fd;
	uint8_t				decimal;
	uint8_t				hash;
	uint8_t				zero;
	uint8_t				z_pad;
	uint8_t				dot;
	uint8_t				plus;
	uint8_t				neg;
	uint8_t				space;
	uint8_t				set_ret;
	uint8_t				rd;
	char				*c;
	char				car;
	int					whold;
	int					phold;
};

char					*ft_fpad(char *s, t_ap *tree);
void					precwidth(int many, t_ap *tree, int prec);
int						bt_putstr_fd(char const *s, t_ap *tree);
int						bt_putchar(char c, int times);
int						bt_strlen(const char *s, t_ap *tree, int prec);
int						count_usize(uintmax_t n);
int						count_size(intmax_t n);
int						zs(t_ap *tree, int i);
void					non(va_list ap, char *format, t_ap *tree);
void					addy(va_list ap, char *format, t_ap *tree);
void					percent(va_list ap, char *format, t_ap *tree);
void					character(va_list ap, char *format, t_ap *tree);
void					str(va_list ap, char *format, t_ap *tree);
void					udigit(va_list ap, char *format, t_ap *tree);
int						count_usize(uintmax_t n);
int						ft_wstrlen(wchar_t *wc);
char					*ft_padder(char *s, t_ap *tree);
void					big_digit(va_list ap, char *format, t_ap *tree);
void					wchar(va_list ap, char *format, t_ap *tree);
int						bt_putwstr(wchar_t *s, t_ap *tree);
char					*ft_wpad(wchar_t *s, t_ap *tree);
int						get_wstr_len(wchar_t *wc);
int						put_wchar(char c);
int						put_wc(wchar_t c);
int						bt_putchar(char c, int times);
void					ft_put_wstr_fd_prec(wchar_t *s, int fd, t_ap *tree);
char					*ft_spad(char *s, t_ap *tree);
char					*fubase(uintmax_t n,
								uintmax_t base, char *format, t_ap *tree);
int						bt_putstr_fd(char const *s, t_ap *tree);
void					floot(va_list ap, char *format, t_ap *tree);
char					*ft_ftoa_base(double n, long long base, char *format);
void					ft_putstr_fd_prec(char *s, t_ap *tree);
int						precision(char *format, va_list ap, t_ap *tree);
char					*ft_maxtoa_base(intmax_t n, intmax_t base,
										char *format);
int						ass_f(void (**p) (va_list ap, char *format,
							t_ap *tree), t_ap *tree);
void					digit(va_list ap, char *format, t_ap *tree);
int						ft_printf(const char *restrict format, ...);
void					flags(char *c, t_ap *tree);
intmax_t				decimals(double holder, float base, t_ap *tree);
intmax_t				ft_abs(intmax_t in);

#endif
