/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flags_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celva <celva@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:12:47 by celva             #+#    #+#             */
/*   Updated: 2019/11/15 16:21:38 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*parsing_flags2(t_flags *c, char *str, char f[6])
{
	int i;

	i = 0;
	while (c->fg[i] != '\0')
		if (c->fg[i++] == '#')
		{
			f[2] = '1';
			str = parsing_hashtag(c, str, f);
		}
	i = 0;
	while (c->fg[i] != '\0')
		if (c->fg[i++] == '+')
		{
			f[3] = '1';
			str = parsing_plus(str, c, f);
		}
	i = 0;
	while (c->fg[i] != '\0')
		if (c->fg[i++] == ' ')
		{
			f[4] = '1';
			str = parsing_space(str, c);
		}
	return (str);
}

char		*parsing_flags(t_flags *c, char *str)
{
	int		i;
	char	f[6];

	ft_strcpy(f, "00000");
	i = 0;
	while (c->fg[i] != '\0')
		if (c->fg[i++] == '-')
		{
			f[0] = '1';
			str = parsing_minus(str, c);
		}
	i = 0;
	while (c->fg[i] != '\0')
		if (c->fg[i++] == '0' && f[0] != '1')
		{
			f[1] = '1';
			if (c->acc != -1 && c->type != 'f')
				str = parsing_zero(str, c->acc);
			else
				str = parsing_zero(str, c->width);
		}
	str = parsing_flags2(c, str, f);
	return (str);
}
