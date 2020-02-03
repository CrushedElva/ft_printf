/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:03:53 by celva             #+#    #+#             */
/*   Updated: 2019/11/19 16:04:47 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	value_err(t_flags *c, char *str)
{
	int i;

	i = 0;
	i = c->width > (int)ft_strlen(str) ? c->width : (int)ft_strlen(str);
	if (c->type != 'c' && c->type != 's')
		i = i > c->acc ? i : c->acc;
	if ((c->type == 'c' || c->type == 'C') && i == 0)
		i++;
	return (i);
}

char		*parsing_string(t_flags *c, va_list ap)
{
	char	*str;
	char	*res;

	str = line_creation(c, ap);
	if (str == NULL && c->type != 'n')
	{
		c->err = -1;
		return (NULL);
	}
	if (c->type != 'f' && c->type != 'n')
		str = insert_accuracy(c, str);
	str = parsing_flags(c, str);
	if (c->width != 0 && ft_strchr(c->fg, '-') == NULL && c->type != 'n')
		str = insert_width(c->width, str, c);
	c->err = value_err(c, str);
	if (c->type == 'n')
		res = NULL;
	else
	{
		res = ft_memalloc(c->err + 1);
		res = ft_memcpy(res, str, c->err + 1);
	}
	ft_memdel((void**)&str);
	return (res);
}

static void	del_list(t_flags *c, char *res_str)
{
	ft_memdel((void**)&res_str);
	ft_memdel((void**)&(c->fg));
	ft_memdel((void**)&c);
}

static char	*cycle_bp(char **format, va_list ap, t_flags *c)
{
	int		len;
	char	*str;

	str = NULL;
	if (**format == '%')
	{
		ft_strclr(c->fg);
		*c = (t_flags){c->fg, -1, -1, 0, 0, 0, c->n};
		str = parsing_type(ap, format, c);
		if (str == NULL && c->err == -1)
			return (NULL);
	}
	else if (**format != '%')
	{
		if (ft_strchr(*format, '%') != NULL)
			len = ft_strchr(*format, '%') - *format;
		else
			len = ft_strlen(*format);
		str = ft_strsub(*format, 0, len);
		*format += (ft_strlen(str) - 1);
		c->err = ft_strlen(str);
	}
	return (str);
}

int			basic_processing(va_list ap, char *format)
{
	int		len;
	char	*str;
	char	*res_str;
	t_flags	*c;

	res_str = ft_memalloc(1);
	c = (t_flags*)ft_memalloc(sizeof(t_flags) * 1);
	c->fg = ft_memalloc(6);
	c->n = 0;
	while (*format != '\0')
	{
		if ((str = cycle_bp(&format, ap, c)) == NULL && c->err == -1)
		{
			del_list(c, res_str);
			return (-1);
		}
		res_str = ft_memjoin_del(res_str, c->n, str, c->err);
		c->n += c->err;
		ft_memdel((void**)&str);
		format++;
	}
	len = c->n;
	write(1, res_str, len);
	del_list(c, res_str);
	return (len);
}
