/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:51:19 by celva             #+#    #+#             */
/*   Updated: 2019/11/19 12:33:36 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*parsing_minus(char *str, t_flags *c)
{
	char	*res;
	int		i;
	int		len;

	if (c->width > (len = ft_strlen(str)))
	{
		if ((c->type == 'c' || c->type == 'C') && len == 0)
			len++;
		res = ft_memalloc(c->width + 1);
		ft_strncpy(res, str, len);
		i = len;
		while (i < c->width)
		{
			res[i] = ' ';
			i++;
		}
		ft_memdel((void**)&str);
		return (res);
	}
	return (str);
}

char		*parsing_space(char *str, t_flags *c)
{
	char *res;

	if ((str[0] != '+' && str[0] != '-') && (c->type == 'f' || c->type == 'd'
			|| c->type == 'D' || c->type == 'i'))
	{
		if (ft_strchr(c->fg, '0') != NULL && str[0] == '0' &&
				ft_isdigit(str[1]) == 1 && (c->acc == -1 || c->type == 'f'))
		{
			str[0] = ' ';
			return (str);
		}
		res = ft_memalloc(ft_strlen(str) + 2);
		res[0] = ' ';
		if (ft_strchr(str, ' ') != NULL)
			ft_strncat((res + 1), str, ft_strlen(str) - 1);
		else
			ft_strcpy((res + 1), str);
		ft_memdel((void**)&str);
		return (res);
	}
	return (str);
}

static char	*pars_plus_f0(char *str)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = ft_memalloc(ft_strlen(str) + 1);
	res[0] = '+';
	i = 1;
	j = 0;
	while (i < ft_strlen(str))
		res[i++] = str[j++];
	return (res);
}

char		*parsing_plus(char *str, t_flags *c, char *f)
{
	char	*res;

	if ((c->type == 'd' || c->type == 'i' || c->type == 'D' || c->type == 'f')
		&& ((str[0] >= '0' && str[0] <= '9') || ft_strlen(str) == 0 ||
			ft_str_symb(str, " ") == 1))
	{
		if (f[0] == '1' && ft_strchr(str, ' ') != NULL)
			res = pars_plus_f0(str);
		else if (f[1] == '1' && str[0] == '0' && ft_isdigit(str[1]) == 1 &&
				(c->acc == -1 || c->type == 'f'))
		{
			str[0] = '+';
			return (str);
		}
		else
		{
			res = ft_memalloc(ft_strlen(str) + 2);
			res[0] = '+';
			ft_strcpy((res + 1), str);
		}
		ft_memdel((void**)&str);
		return (res);
	}
	return (str);
}

char		*parsing_zero(char *str, int width)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str);
	if (width > len)
	{
		res = ft_memalloc(width + 1);
		i = 0;
		j = 0;
		if (str[0] == '-')
		{
			res[0] = '-';
			i++;
		}
		while (j++ < (width - len))
			res[i++] = '0';
		j = (str[0] == '-') ? 1 : 0;
		while (str[j] != '\0')
			res[i++] = str[j++];
		ft_memdel((void**)&str);
		return (res);
	}
	return (str);
}
