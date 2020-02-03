/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:52:40 by celva             #+#    #+#             */
/*   Updated: 2019/11/15 15:52:42 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	type_conversion(unsigned long long arg, t_flags *c)
{
	if (c->spec == 1 && (ft_isupper(c->type) == 0 || c->type == 'X'))
		arg = (unsigned char)arg;
	if (c->spec == 2 && (ft_isupper(c->type) == 0 || c->type == 'X'))
		arg = (unsigned short int)arg;
	if (c->spec == 0 && (ft_isupper(c->type) == 0 || c->type == 'X'))
		arg = (unsigned int)arg;
	if (c->spec == 3 && (ft_isupper(c->type) == 0 || c->type == 'X'))
		arg = (unsigned long)arg;
	if (ft_isupper(c->type) == 1 && c->type != 'X')
		c->type = ft_tolower(c->type);
	return ((unsigned long long)arg);
}

/*
**	ф-ия переводит в 8-ую и возвращает строку
*/

char						*sym_uns_octal(unsigned long long arg, t_flags *c)
{
	char	*res;
	char	*res1;
	int		i;
	int		j;

	arg = type_conversion(arg, c);
	res = (char*)ft_memalloc(count_symb(((long long)arg), 8) + 1);
	res1 = (char*)ft_memalloc(count_symb(((long long)arg), 8) + 1);
	if (arg == 0)
	{
		res1[0] = '0';
		ft_memdel((void**)&res);
		return (res1);
	}
	i = 0;
	while (arg != 0)
	{
		res[i++] = (arg % 8) + '0';
		arg /= 8;
	}
	j = 0;
	while (--i >= 0)
		res1[j++] = res[i];
	ft_memdel((void**)&res);
	return (res1);
}

static int					sym_uns_hex_str(t_flags *c, unsigned long long arg,
															char *res)
{
	unsigned long long	p;
	int					i;

	i = 0;
	while (arg != 0)
	{
		if ((p = arg % 16) > 9 && c->type == 'X')
			res[i++] = p + 55;
		else if (p > 9 && (c->type == 'x' || c->type == 'p'))
			res[i++] = p + 87;
		else
			res[i++] = p + '0';
		arg /= 16;
	}
	return (i);
}

/*
**	ф-ия переводит в 16-ую и возвращает строку
*/

char						*sym_uns_hex(unsigned long long arg, t_flags *c)
{
	char				*res;
	char				*res1;
	int					i;
	int					p;

	if (c->type != 'p')
		arg = type_conversion(arg, c);
	res = (char*)ft_memalloc(count_symb(((unsigned long long)arg), 16) + 1);
	res1 = (char*)ft_memalloc(count_symb(((unsigned long long)arg), 16) + 1);
	if (arg == 0)
	{
		res1[0] = '0';
		ft_memdel((void**)&res);
		return (res1);
	}
	i = sym_uns_hex_str(c, arg, res);
	p = 0;
	while (--i >= 0)
		res1[p++] = res[i];
	ft_memdel((void**)&res);
	return (res1);
}

/*
**	ф-ия переводит в 2-ую и возвращает строку
*/

char						*sym_binary(unsigned long long arg, t_flags *c)
{
	char		*res;
	char		*res1;
	long long	i;

	arg = type_conversion(arg, c);
	res = (char*)ft_memalloc(count_symb(((unsigned long long)arg), 2) + 1);
	res1 = (char*)ft_memalloc(count_symb(((unsigned long long)arg), 2) + 1);
	if (arg == 0)
	{
		res1[0] = '0';
		ft_memdel((void**)&res);
		return (res1);
	}
	i = 0;
	while (arg != 0)
	{
		res[i++] = (arg % 2) + '0';
		arg /= 2;
	}
	arg = 0;
	while (--i >= 0)
		res1[arg++] = res[i];
	ft_memdel((void**)&res);
	return (res1);
}
