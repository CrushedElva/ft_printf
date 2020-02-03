/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:26:06 by celva             #+#    #+#             */
/*   Updated: 2019/11/15 15:25:16 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*add_digit(char *str)
{
	char	*res;

	res = ft_memalloc(ft_strlen(str) + 2);
	res[0] = '1';
	ft_strcpy(res + 1, str);
	ft_memdel((void**)&str);
	return (res);
}

static char	*fl_str_create_res(int i, char *str)
{
	i--;
	if (str[i] >= '5' && str[i] <= '9')
	{
		str[i] = '\0';
		while (i >= 0)
		{
			i--;
			if (str[i] == '.')
				i--;
			if (str[i] == '9')
				str[i] = '0';
			else
			{
				str[i] = str[i] + 1;
				break ;
			}
		}
		if (i == -1)
			str = add_digit(str);
	}
	else
		str[i] = '\0';
	return (str);
}

static char	*fl_str_create(long double res, int flag, int ua, int j)
{
	int		wp;
	int		i;
	char	*str;

	i = 0;
	if (flag == 1)
	{
		str = ft_memalloc(ua + j + 2);
		str[0] = '-';
		str++;
	}
	else
		str = ft_memalloc(ua + j + 1);
	while (i < (ua + j + 1))
	{
		if (i == j && ua == 0)
			break ;
		if (i == j)
			str[i++] = '.';
		wp = (int)(res * 10);
		str[i++] = wp + '0';
		res *= 10;
		res -= wp;
	}
	return (fl_str_create_res(i, str));
}

static char	*ft_float(t_flags *c, long double res, int flag, int j)
{
	int		ua;
	char	*str;

	ua = c->acc == -1 ? 7 : c->acc + 1;
	if (j == 0)
		j++;
	str = fl_str_create(res, flag, ua, j);
	if (c->acc == 0 && ft_strchr(c->fg, '#') == NULL)
		*ft_strchr(str, '.') = '\0';
	if (flag == 1)
		str--;
	return (str);
}

char		*sym_float(long double d, t_flags *c)
{
	int			j;
	int			flag;
	long double	res;

	flag = 0;
	if (d < 0)
	{
		flag = 1;
		d = -d;
	}
	res = d;
	if (res < 1)
		res /= 10;
	j = 0;
	while (res >= 1)
	{
		res /= 10;
		j++;
	}
	return (ft_float(c, res, flag, j));
}
