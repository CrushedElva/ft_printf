/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:16:46 by celva             #+#    #+#             */
/*   Updated: 2019/11/19 14:21:05 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	ф-ия обрабатывает char
*/

char		*sym_char(int arg)
{
	char	*res;

	res = NULL;
	res = (char*)ft_memalloc(2);
	res[0] = arg;
	return (res);
}

static char	*sym_char_unic_d(wint_t g)
{
	char *res;

	if (g >= 2048 && g <= 65535)
	{
		res = (char*)ft_memalloc(4);
		res[0] = (g >> 12) + 224;
		res[1] = ((g >> 6) & 63) + 128;
		res[2] = ((g & 63) + 128);
	}
	if (g >= 65536)
	{
		res = (char*)ft_memalloc(5);
		res[0] = (g >> 18) + 240;
		res[1] = ((g >> 12) & 63) + 128;
		res[2] = ((g >> 6) & 63) + 128;
		res[3] = ((g & 63) + 128);
	}
	return (res);
}

char		*sym_char_unic(wint_t g)
{
	char	*res;

	res = NULL;
	if (g <= 127)
	{
		res = (char*)ft_memalloc(2);
		res[0] = g;
	}
	if (g >= 127 && g <= 2047)
	{
		res = (char*)ft_memalloc(3);
		res[0] = (g >> 6) + 192;
		res[1] = ((g & 63) + 128);
	}
	else
		res = sym_char_unic_d(g);
	return (res);
}
