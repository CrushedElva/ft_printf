/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:49:14 by celva             #+#    #+#             */
/*   Updated: 2019/11/19 14:12:33 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*sym_string(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if (str == NULL)
	{
		res = ft_memalloc(7);
		res = ft_strcpy(res, "(null)");
	}
	else
	{
		res = ft_memalloc(ft_strlen(str) + 1);
		res = ft_strcpy(res, str);
	}
	return (res);
}

static char	*sym_wstring(wchar_t *str, t_flags *c)
{
	char	*res;
	char	*sym;
	int		i;

	i = 0;
	if (str == NULL)
	{
		res = ft_memalloc(7);
		res = ft_strcpy((char*)res, "(null)");
	}
	if (str != NULL)
	{
		res = ft_memalloc(1);
		while (str[i] != '\0')
		{
			sym = sym_char_unic((unsigned long)str[i]);
			if (((int)(ft_strlen(res) + ft_strlen(sym)) > c->acc)
												&& c->acc != -1)
				break ;
			res = ft_strjoin_del(res, sym);
			ft_memdel((void**)&sym);
			i++;
		}
	}
	return ((char*)res);
}

static char	*line_creation2(t_flags *c, va_list ap)
{
	char	*res;
	int		*res_n;

	res = NULL;
	res_n = NULL;
	if (c->type == '%')
	{
		res = ft_memalloc(2);
		res[0] = '%';
	}
	else if (c->type == 'p')
		res = sym_point((va_arg(ap, long long)), c);
	else if (c->type == 'f' && c->spec == 6)
		res = sym_float(va_arg(ap, long double), c);
	else if (c->type == 'f')
		res = sym_float((long double)(va_arg(ap, double)), c);
	else if (c->type == 'b' || c->type == 'B')
		res = sym_binary((va_arg(ap, unsigned long long)), c);
	else if (c->type == 'n')
	{
		res_n = va_arg(ap, int*);
		*res_n = c->n;
	}
	return (res);
}

/*
**	по-идее ф-ия, которая создает строку, которую нужно будет вывести
**	без ширины и флагов
*/

char		*line_creation(t_flags *c, va_list ap)
{
	char *res;

	res = NULL;
	if (c->type == 'd' || c->type == 'i' || c->type == 'D')
		res = sym_decimal(va_arg(ap, long long), c);
	else if (c->type == 'o' || c->type == 'O')
		res = sym_uns_octal((va_arg(ap, unsigned long long)), c);
	else if (c->type == 'u' || c->type == 'U')
		res = sym_uns_decimal((va_arg(ap, unsigned long long)), c);
	else if (c->type == 'x' || c->type == 'X')
		res = sym_uns_hex((va_arg(ap, unsigned long long)), c);
	else if ((c->type == 's' && c->spec == 3) || c->type == 'S')
		res = sym_wstring(va_arg(ap, wchar_t*), c);
	else if ((c->type == 's' || c->type == 'S') && c->spec != 3)
		res = sym_string(va_arg(ap, char*));
	else if ((c->type == 'c' && c->spec == 3) || c->type == 'C')
		res = sym_char_unic((unsigned long)(va_arg(ap, unsigned long)));
	else if (c->type == 'c')
		res = sym_char(va_arg(ap, int));
	else if (c->type == '%' || c->type == 'p' || c->type == 'f' ||
				c->type == 'b' || c->type == 'B' || c->type == 'n')
		res = line_creation2(c, ap);
	return (res);
}
