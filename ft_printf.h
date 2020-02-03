/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:36:12 by marvin            #+#    #+#             */
/*   Updated: 2019/11/19 12:25:38 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <ctype.h>
# include "libft.h"
# define ULLONG_MAX	0xFFFFFFFFFFFFFFFFULL

typedef struct	s_flags
{
	char	*fg;
	int		width;
	int		acc;
	int		spec;
	char	type;
	int		err;
	int		n;
}				t_flags;

int				count_symb(unsigned long long arg, unsigned int system);
char			*sym_uns_hex_ll(long long arg, char c);
char			*sym_uns_octal(unsigned long long arg, t_flags *c);
char			*sym_uns_hex(unsigned long long arg, t_flags *c);
char			*sym_uns_decimal(unsigned long long arg, t_flags *c);
char			*sym_decimal(long long arg, t_flags *c);
char			*sym_point(long long arg, t_flags *c);
char			*parsing_zero(char *str, int width);
char			*parsing_plus(char *str, t_flags *c, char *f);
char			*parsing_space(char *str, t_flags *c);
char			*parsing_minus(char *str, t_flags *c);
char			*parsing_hashtag(t_flags *c, char *str, char *f);
char			*line_creation(t_flags *c, va_list ap);
int				check_simbol_format(char c);
int				parsing_specifier(char *fst, t_flags *c);
char			*insert_accuracy(t_flags *c, char *str);
char			*insert_width(int width, char *str, t_flags *c);
char			*parsing_flags(t_flags *c, char *str);
char			*parsing_string(t_flags *c, va_list ap);
char			*parsing_type(va_list ap, char **s, t_flags *c);
int				basic_processing(va_list ap, char *format);
char			*sym_char(int arg);
char			*sym_char_unic(wint_t g);
char			*sym_float(long double d, t_flags *c);
char			*sym_binary(unsigned long long arg, t_flags *c);
int				ft_printf(const char *format, ...);
#endif
