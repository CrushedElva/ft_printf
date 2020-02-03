/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:02:29 by celva             #+#    #+#             */
/*   Updated: 2019/11/19 14:17:44 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	ф-ия записывает в строку указатель
*/

char	*sym_point(long long arg, t_flags *c)
{
	char *res;
	char *prom;
	char *new;

	new = (char*)ft_memalloc(sizeof(char) * 3);
	new[0] = '0';
	new[1] = 'x';
	if (c->acc == 0)
		return (new);
	prom = sym_uns_hex(((unsigned long long)arg), c);
	res = ft_strjoin(new, prom);
	ft_memdel((void**)&new);
	ft_memdel((void**)&prom);
	return (res);
}

/*
**	ф-ия для беззнакового инта
*/

char	*sym_uns_decimal(unsigned long long arg, t_flags *c)
{
	char *res;
	char *new;
	char *res1;

	if (c->spec == 1 && c->type != 'U')
		arg = (unsigned char)arg;
	if (c->spec == 2 && c->type != 'U')
		arg = (unsigned short int)arg;
	if (c->spec == 0 && c->type != 'U')
		arg = (unsigned int)arg;
	if (c->spec == 3 || c->type == 'U')
		arg = (unsigned long)arg;
	res = ft_itoa_ull((unsigned long long)arg, '+');
	new = res;
	if (*res == '-')
		res++;
	res1 = (char*)ft_memalloc(sizeof(char) * (ft_strlen(res) + 1));
	ft_strcpy(res1, res);
	ft_memdel((void**)&new);
	return (res1);
}

char	*sym_decimal(long long arg, t_flags *c)
{
	char *res;

	if (c->spec == 1 && c->type != 'D')
		arg = (signed char)arg;
	if (c->spec == 2 && c->type != 'D')
		arg = (short int)arg;
	if (c->spec == 0 && c->type != 'D')
		arg = (int)arg;
	if (c->spec == 3 && c->type != 'D')
		arg = (long)arg;
	res = ft_itoa((long long)arg);
	return (res);
}

/*
**	ф-ия, которая считает кол-во символов для любой
**	системы счисления при переводе из десятичной
*/

int		count_symb(unsigned long long arg, unsigned int system)
{
	int					i;
	unsigned long long	res;
	unsigned long long	buf;

	i = 0;
	res = 1;
	if (arg == 0)
		return (1);
	if (arg == ULLONG_MAX && system == 16)
		return (16);
	if (arg == ULLONG_MAX && system == 2)
		return (64);
	if (arg == ULLONG_MAX && system == 8)
		return (22);
	while (res < (arg + 1))
	{
		buf = res;
		res *= system;
		if (buf > res)
			return (i + 1);
		i++;
	}
	return (i);
}
