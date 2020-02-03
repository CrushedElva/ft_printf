/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parsing_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:09:17 by celva             #+#    #+#             */
/*   Updated: 2019/11/19 15:09:49 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parsing_i3(va_list ap, t_flags *c, char **s)
{
	(*s)++;
	if (**s == '*')
	{
		c->acc = va_arg(ap, int);
		if (c->acc < 0)
			c->acc = -1;
	}
	else if (**s <= '9' && **s >= '0')
	{
		c->acc = ft_atoi(*s);
		while (*(*s + 1) >= '0' && *(*s + 1) <= '9')
			(*s)++;
	}
	else
	{
		c->acc = 0;
		(*s)--;
	}
}

static void	parsing_i(va_list ap, char **s, t_flags *c, int i)
{
	if (i == 1)
		if (ft_strchr((c->fg), **s) == NULL)
			*(ft_strchr((c->fg), '\0')) = **s;
	if (i == 4)
		if (!((c->spec == 1 && **s == 'h') || (c->spec == 5 && **s == 'l')))
			c->spec = parsing_specifier(*s, c);
	if (i == 0)
	{
		if (**s == '*')
		{
			c->width = va_arg(ap, int);
			if (c->width < 0)
			{
				c->width *= -1;
				*(ft_strchr((c->fg), '\0')) = '-';
			}
		}
		else
		{
			c->width = ft_atoi(*s);
			(*s) = (*s) + ft_intlen(c->width) - 1;
		}
	}
	if (i == 3)
		parsing_i3(ap, c, s);
}

char		*parsing_type(va_list ap, char **s, t_flags *c)
{
	int i;
	int j;

	(*s)++;
	j = 0;
	while (**s != 'd' && **s != 'i' && **s != 'o' && **s != 'u' && **s != 'B' &&
		**s != 'x' && **s != 'X' && **s != 'f' && **s != 'F' && **s != 'b' &&
		**s != 'e' && **s != 'E' && **s != 'a' && **s != 'A' && **s != 'O' &&
		**s != 'c' && **s != 's' && **s != 'S' && **s != 'p' && **s != 'D' &&
		**s != 'n' && **s != '%' && **s != 'U' && **s != 'C')
	{
		i = check_simbol_format(**s);
		parsing_i(ap, s, c, i);
		if (i == 5)
		{
			(*s)--;
			return (NULL);
		}
		(*s)++;
	}
	c->type = **s;
	return (parsing_string(c, ap));
}
