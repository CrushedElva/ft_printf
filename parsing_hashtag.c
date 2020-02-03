/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hashtag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:59:09 by celva             #+#    #+#             */
/*   Updated: 2019/11/15 12:53:33 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pars_hash_f0_xo(t_flags *c, char *res)
{
	int i;

	if (c->type == 'o')
	{
		res[0] = '0';
		i = 1;
	}
	if (c->type == 'x' || c->type == 'X')
	{
		res[0] = '0';
		res[1] = c->type;
		i = 2;
	}
	return (i);
}

static char	*pars_hash_f0(t_flags *c, char *str)
{
	char	*res;
	int		i;
	int		len;

	if ((ft_str_symb(str, "0 ") == 1 && (str[0] != ' ' || c->type != 'o'))
		|| (str[0] == '0' && ft_strchr(str, ' ') && c->type == 'o'))
		return (str);
	len = ft_strlen(str);
	if (c->type != 'o' && (str[len - 1] != ' ' || str[len - 2] != ' '))
	{
		res = ft_memalloc(len + 2);
		len++;
	}
	else
		res = ft_memalloc(len + 1);
	i = pars_hash_f0_xo(c, res);
	if (len == c->acc && str[0] == '0' && ft_isdigit(str[1]) == 1)
		ft_strncat((res + i), (str + i), len - i);
	else
		ft_strncat((res + i), str, len - i);
	ft_memdel((void**)&str);
	return (res);
}

static char	*pars_hash_o(char *str)
{
	char *res;

	if (ft_strlen(str) == 0)
	{
		res = ft_memalloc(2);
		res[0] = '0';
		ft_memdel((void**)&str);
		return (res);
	}
	else if (str[0] > '0' && str[0] <= '9')
	{
		res = ft_memalloc(ft_strlen(str) + 2);
		res[0] = '0';
		ft_strcpy((res + 1), str);
		ft_memdel((void**)&str);
		return (res);
	}
	return (str);
}

static char	*pars_hash_x(char *str, t_flags *c)
{
	char	*res;
	int		flag;

	flag = 0;
	if (ft_strchr(c->fg, '0') != NULL && str[0] == '0' &&
			str[1] != '0' && c->acc == -1)
	{
		res = ft_memalloc(ft_strlen(str) + 2);
		flag = 1;
	}
	else
		res = ft_memalloc(ft_strlen(str) + 3);
	res[0] = '0';
	res[1] = c->type;
	if (flag == 1)
		ft_strcpy((res + 2), (str + 1));
	else
		ft_strcpy((res + 2), str);
	ft_memdel((void**)&str);
	return (res);
}

char		*parsing_hashtag(t_flags *c, char *str, char *f)
{
	if (c->type != 'o' && c->type != 'x' && c->type != 'X')
		return (str);
	if (f[1] == '1' && (c->type == 'x' || c->type == 'X') && str[0] == '0' &&
			str[1] == '0' && ft_str_symb(str, "0 ") == 0 && c->acc == -1)
		str[1] = c->type;
	else if (f[1] == '1' && c->type == 'o' && str[0] == '0')
		str[0] = '0';
	else if (f[0] == '1' && ft_strchr(str, ' ') != NULL)
		return (pars_hash_f0(c, str));
	else if (c->type == 'o')
		return (pars_hash_o(str));
	else if ((c->type == 'x' || c->type == 'X') && ft_str_symb(str, "0 ") == 0)
		return (pars_hash_x(str, c));
	return (str);
}
