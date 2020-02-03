/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_w_pars_spec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:25:16 by celva             #+#    #+#             */
/*   Updated: 2019/11/15 16:25:53 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	ф-ия определяет что за символ: флаг, тип, точность или ширина
*/

int		check_simbol_format(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
		return (1);
	if (c == 'd' || c == 'i' || c == 'O' || c == 'o' || c == 'u' || c == 'x'
		|| c == 'D' || c == 'X' || c == 'f' || c == 'F' || c == 'e' || c == 'E'
		|| c == 'b' || c == 'g' || c == 'G' || c == 'a' || c == 'A' || c == 'c'
		|| c == 'U' || c == 's' || c == 'S' || c == 'p' || c == 'n' || c == '%'
		|| c == 'B')
		return (2);
	if (c == '.')
		return (3);
	if (c == 'l' || c == 'h' || c == 'j' || c == 'z' || c == 't' || c == 'L')
		return (4);
	if ((c >= '0' && c <= '9') || c == '*')
		return (0);
	return (5);
}

int		parsing_specifier_more(int s, t_flags *c)
{
	if (s > c->spec)
		return (s);
	return (c->spec);
}

int		parsing_specifier(char *fst, t_flags *c)
{
	int i;

	i = 0;
	while (fst[i] != '\0')
	{
		if (fst[i] == 'h' && fst[i + 1] == 'h')
			return (parsing_specifier_more(1, c));
		if (fst[i] == 'h')
			return (parsing_specifier_more(2, c));
		if (fst[i] == 'l')
			return (parsing_specifier_more(3, c));
		if (fst[i] == 'z')
			return (parsing_specifier_more(4, c));
		if (fst[i] == 'l' && fst[i + 1] == 'l')
			return (parsing_specifier_more(5, c));
		if (fst[i] == 'L')
			return (parsing_specifier_more(6, c));
		if (fst[i] == 'j')
			return (parsing_specifier_more(7, c));
		i++;
	}
	return (0);
}

char	*insert_width(int width, char *str, t_flags *c)
{
	int		len;
	char	*res;
	int		i;
	int		j;

	if ((c->type == 'c' || c->type == 'C') && ft_strlen(str) == 0)
		len = 1;
	else
		len = ft_strlen(str);
	if (width > len)
	{
		res = ft_memalloc(width + 1);
		i = 0;
		while (i < (width - len))
			res[i++] = ' ';
		j = 0;
		while (str[j] != '\0')
			res[i++] = str[j++];
		ft_memdel((void**)&str);
		return (res);
	}
	return (str);
}
