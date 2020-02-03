/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_accuracy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:44:06 by celva             #+#    #+#             */
/*   Updated: 2019/11/15 15:47:36 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*acc_more(t_flags *c, char *str, int len)
{
	char	*res;
	int		i;
	int		j;

	if (str[0] == '-')
	{
		res = ft_memalloc(c->acc + 2);
		res[0] = '-';
		i = 1;
		while (i < (c->acc - len + 1))
			res[i++] = '0';
	}
	else
	{
		res = ft_memalloc(c->acc + 1);
		i = 0;
		while (i < (c->acc - len))
			res[i++] = '0';
	}
	j = (str[0] == '-') ? 1 : 0;
	while (str[j] != '\0')
		res[i++] = str[j++];
	ft_memdel((void**)&str);
	return (res);
}

static char	*acc_less(t_flags *c, char *str)
{
	int		i;
	int		j;
	char	*res;

	res = ft_memalloc(c->acc + 1);
	i = 0;
	j = 0;
	while (i < c->acc)
		res[i++] = str[j++];
	ft_memdel((void**)&str);
	return (res);
}

static char	*acc_point(t_flags *c, char *str)
{
	char	*res;
	char	*str_1;
	char	*buf;
	char	*accu;
	int		i;

	str_1 = str;
	str += 2;
	accu = ft_memalloc(c->acc + 1);
	i = 0;
	while (i < c->acc - (int)ft_strlen(str))
		accu[i++] = '0';
	if (ft_strlen(str) != 0)
		buf = ft_strjoin(accu, str);
	res = ft_strjoin("0x", buf);
	ft_memdel((void**)&buf);
	ft_memdel((void**)&str_1);
	ft_memdel((void**)&accu);
	return (res);
}

char		*insert_accuracy(t_flags *c, char *str)
{
	char	*res;
	int		len;

	if (str[0] == '-')
		len = ft_strlen(str) - 1;
	else
		len = ft_strlen(str);
	if ((len < c->acc) && c->type != 'c' && c->type != 's' && c->type != 'p'
			&& c->type != 'C' && c->type != 'S')
		return (acc_more(c, str, len));
	else if (c->acc == 0 && c->type != '%' && c->type != 'p' &&
												ft_atoi(str) == 0)
	{
		res = ft_memalloc(c->acc + 1);
		ft_memdel((void**)&str);
		return (res);
	}
	else if (c->type == 'p' && c->acc > (int)ft_strlen(str) - 2)
		return (acc_point(c, str));
	else if (len > c->acc && (c->type == 's' || c->type == 'S') && c->acc != -1)
		return (acc_less(c, str));
	return (str);
}
